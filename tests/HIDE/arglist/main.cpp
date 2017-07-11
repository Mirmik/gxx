#include <gxx/arglist.h>
#include <gxx/debug/testclass.h>
#include <iostream>

using namespace gxx::literals;

template<typename T>
int genfunc(const T* ref, int i) {
	dprln("genfunc default");
}

template<>
int genfunc(const int* ref, int i) {
	//dpr("genfunc int ");
	dprln(*ref);
}

template<>
int genfunc(const char* const* ref, int i) {
	//dpr("genfunc string ");
	//dprptrln(&ref);
	dprln(*ref);
}

struct test_generic {
	template<typename T>
	using FuncPtr = int(*)(const T*, int i); 
	using VoidFuncPtr = int(*)(void*, int i); 

	template <typename T>
	static FuncPtr<T> function_pointer() { 
		//pretty_that_function();dprln();
		return &genfunc<T>; 
	}

	static int visit(gxx::argument arg, int i) {
		return reinterpret_cast<VoidFuncPtr>(arg.func)(arg.ptr, i);
	}
};

/*template<typename ... T>
int func_impl(T&& ... args) {
	//pretty_that_function();dprln();
	gxx::arglist list(gxx::make_argument<test_generic>(std::forward<T>(args)) ...);

	for(auto& v : list) {
		test_generic::visit(v, 1024);
	}
}*/

int func_impl(gxx::arglist&& list) {
	//gxx::arglist list(gxx::make_argument<test_generic>(std::forward<T>(args)) ...);

	for(auto v : list) {
		test_generic::visit(v, 1024);
	}
}

template<typename ... T>
int func(T&& ... args) {
	//pretty_that_function();dln();
	return func_impl(gxx::arglist(gxx::make_argument<test_generic>(gxx::make_argument_temporary(std::forward<T>(args))) ...));
}


int main() {
	int i = 42;
	TestClass t;
	const char* msg = "Message";
	char msg2[] = "Message2";

	//func(42, "Message");
	func(msg2,  42, "Message", TestClass(), i, msg, t, "1"_a=42, "2"_a="Message", "3"_a=TestClass(), "4"_a=i, "5"_a=msg, "6"_a=t);
	// TestClass(), t, "pair"_a = t, "num"_a=328, "mirmik"_a="saldo", "msg"_a=named_msg
	//"pair"_a = t, "num"_a=328, "mirmik"_a="saldo", "msg"_a=named_msg 
}