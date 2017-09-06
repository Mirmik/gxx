#include <gxx/arglist2.h>
#include <gxx/debug/dprint.h>

using namespace gxx::argument_literal;

//using visitor = argument_visitor<void>;

GXX_REGISTER_ARGUMENT_VISITOR(format_visitor, int(*)(void*, int));

int hello(int& i, int t) {
	dpr("HelloWorld "); dprln(i); dprln(t);
	return t + 1;
}

int hello_str(const char* i, int t) {
	dpr("HelloWorld "); dprln(i); dprln(t);
	return t + 1;
}

GXX_REGISTER_ARGUMENT_VISIT(format_visitor, int, hello);
GXX_REGISTER_ARGUMENT_VISIT(format_visitor, const char*, hello_str);

template <typename ... Args>
void func(Args&& ... inargs) {	
	auto args = gxx::make_visitable_arglist<format_visitor>(std::forward<Args>(inargs) ...);

	format_visitor::visit(args["a"], 2);
	format_visitor::visit(args[0], 3);
	format_visitor::visit(args[1], 4);
	format_visitor::visit(args[2], 5);
}

int main() {
	int i = 8;
	int m = 9;

	func("a"_a="Mirmik", i, "hello");
}