#include <gxx/arglist.h>
#include <gxx/debug/dprint.h>

using namespace gxx::argument_literal;

class A {
	int i = 42;
public:
	int mtd() {
		dprln(i);
	} 
};

template <typename T> struct print_functions;

template <> struct print_functions<A> : print_functions_basic { static void print(A& a, int i) { a.mtd(); dprln(i); }};
template <> struct print_functions<int> { static void print(int& a, int i) { dprln(a); dprln(i); }};
template <> struct print_functions<char*> { static void print(char* a, int i) { dprln(a); dprln(i); }};

struct format_visitor {
	using ftype = int(*)(void*, int);												

	//template<typename Object> static int visit_implementation(void* obj, int i) {
	//	return reinterpret_cast<Object*>(obj)->mtd(i);
	//}
	template<typename Object>
	static void* get_visit() {
		return (void*) visit_helper<Object>::print;
	}
																			
	template<typename ... Args>												
	static auto visit(gxx::visitable_argument varg, Args&& ... args) {		
		ftype fptr = (ftype) varg.visit;									
		return fptr(varg.ptr, std::forward<Args>(args) ...);				
	}																		
};

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