#include <iostream>
#include <gxx/format.h>

using namespace gxx::argument_literal;
//using namespace gxx::print_funcs;

int main() {
	char world[] = "World";
	const char* world2 = "World";
	int i = 456;

	std::string str;

	str = gxx::fmt::format("int {}", 42);
	dprln(str);
	
	str = gxx::fmt::format("string {}", "world");
	dprln(str);
	
	str = gxx::fmt::format("rint {}", i);
	dprln(str);
	
	str = gxx::fmt::format("float {}", (float)1.89);
	dprln(str);

	str = gxx::fmt::format("double {}", (double)1.83);
	dprln(str);

	str = gxx::fmt::format("astring {}", world);
	dprln(str);
	
	str = gxx::fmt::format("pstring {}", world2);
	dprln(str);
	
	str = gxx::fmt::format("int {a}", "a"_a=42);
	dprln(str);
	
	str = gxx::fmt::format("string {a}", "a"_a=std::string("world"));
	dprln(str);
	
	str = gxx::fmt::format("rint {a}", "a"_a=i);
	dprln(str);
	
	str = gxx::fmt::format("astring {a}", "a"_a=world);
	dprln(str);
	
	str = gxx::fmt::format("pstring {a}", "a"_a=world2);
	dprln(str);
	
	gxx::fmt::print("pstring {a}\r\n", "a"_a=world2);
}