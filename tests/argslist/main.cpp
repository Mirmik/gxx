#include <gxx/arglist.h>
#include <gxx/debug/dprint.h>

using namespace gxx::argument_literal;

//using visitor = argument_visitor<void>;

//GXX_REGISTER_ARGUMENT_VISITOR(format_visitor, int(*)(void*, int));

//int hello(int& i, int t) {
//	dpr("HelloWorld "); dprln(i); dprln(t);
//	return t + 1;
//}

//int hello_str(const char* i, int t) {
//	dpr("HelloWorld "); dprln(i); dprln(t);
//	return t + 1;
//}

//GXX_REGISTER_ARGUMENT_VISIT(format_visitor, int, hello);
//GXX_REGISTER_ARGUMENT_VISIT(format_visitor, const char*, hello_str);

class A {
public:

	int mtd(int i) {
		dprln("mtd");
	} 
};

struct format_visitor {
	using ftype = int(*)(void*, int);												

	template<typename Object> static int visit_implementation(void* obj, int i) {
		return reinterpret_cast<Object*>(obj)->mtd(i);
	}
	
	//template<typename Object> static void* get_visit() {
	//	return reinterpret_cast<void*>(&visit_implementation<Object>);
	//} 						
																			
	template<typename ... Args>												
	static auto visit(gxx::visitable_argument varg, Args&& ... args) {		
		ftype fptr = (ftype) varg.visit;									
		return fptr(varg.ptr, std::forward<Args>(args) ...);				
	}																		
};

template<> int format_visitor::visit_implementation<int>(void* ptr, int i) {
	int& obj = *(int*)ptr;

	dprln(i);
	dprln(obj);
}

template<> int format_visitor::visit_implementation<char*>(void* ptr, int i) {
	const char* obj = (const char*) ptr;

	dprln(i);
	dprln(obj);
}

template <typename ... Args>
void func(Args&& ... inargs) {	
	gxx::visitable_argument buffer[sizeof ... (Args)];
	auto args = gxx::make_visitable_arglist<format_visitor>(buffer, std::forward<Args>(inargs) ...);

	//format_visitor::visit(args["a"], 2);
	format_visitor::visit(args[0], 3);
	format_visitor::visit(args[1], 4);
	format_visitor::visit(args[2], 5);
}

int main() {
	int i = 8;
	int m = 9;

	func(33, "hello", A());
}