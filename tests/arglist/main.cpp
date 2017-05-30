#include <gxx/arglist.h>
#include <iostream>

template<typename T>
int genfunc(const T& ref, int i) {
	dprln("genfunc");
}

template<>
int genfunc(const int& ref, int i) {
	dprln("genfunc int");
}

template<>
int genfunc(const char* const& ref, int i) {
	dprln("genfunc string");
}

struct test_generic {
	template<typename T>
	using FuncPtr = int(*)(const T&, int i); 
	using VoidFuncPtr = int(*)(void*, int i); 

	template <typename T>
	static FuncPtr<T> function_pointer() { return &genfunc<T>; }

	static int visit(gxx::argument arg, int i) {
		return reinterpret_cast<VoidFuncPtr>(arg.func)(arg.ptr, i);
	}
};

/*using namespace gxx::literals;

template<typename T>
int func(const T& ptr, int i) {
	printf("func%s%d", __PRETTY_FUNCTION__, i);
}

struct test_generic {
	template<typename T>
	using FuncPtr = int(*)(const T&, int i); 

	template <typename T>
	static FuncPtr<T> function_pointer() { return &func<T>; }
};

class test_visitor {
public:
	int visit(gxx::argument arg, int i) {
		dprln(arg.type_to_string());
		switch (arg.type) {
			case gxx::argument::Type::SInt8:  return 	visit_int64 (arg.i8,  i);
			case gxx::argument::Type::SInt16: return 	visit_int64 (arg.i16, i);
			case gxx::argument::Type::SInt32: return 	visit_int64 (arg.i32, i);
			case gxx::argument::Type::SInt64: return 	visit_int64 (arg.i64, i);
			case gxx::argument::Type::UInt8:  return 	visit_uint64(arg.u8,  i);
			case gxx::argument::Type::UInt16: return 	visit_uint64(arg.u16, i);
			case gxx::argument::Type::UInt32: return 	visit_uint64(arg.u32, i);
			case gxx::argument::Type::UInt64: return 	visit_uint64(arg.u64, i);
			case gxx::argument::Type::CharPtr: return 	visit_cstring(arg.str, i);
			case gxx::argument::Type::CustomType: return 	visit_custom(arg.custom, i);
		}
	}

	int visit_int64(const int64_t& i, int s) {
		dprln(i);	
	}

	int visit_uint64(const uint64_t& i, int s) {
		dprln(i);	
	}

	int visit_cstring(const char*& i, int s) {
		dprln(i);	
	}

	int visit_custom(const gxx::argument::custom_value& c, int s) {
		reinterpret_cast<void(*)(void*,int)>(c.func)(c.ptr, s);
	}
};

template<typename ... Args>
void do_nothing(Args&& ... args) {}
*/
template<typename ... T>
int func(T&& ... args) {
	gxx::arglist list(gxx::make_argument<test_generic>(args) ...);

	for(auto& v : list) {
		test_generic::visit(v, 1024);
	}
}

//class A {};

int main() {
	const char* msg = "Hello";
	//func(40000, "hello2", A());
	const int i = 98;
	func(40, "hello", i, msg);
}