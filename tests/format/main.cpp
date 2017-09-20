#include <iostream>
#include <gxx/format.h>

using namespace gxx::argument_literal;
using namespace gxx::print_funcs;

int main() {
	char world[] = "World";
	const char* world2 = "World";
	int i = 456;

	std::string str;

	str = gxx::format("int {}", 42);
	dprln(str);
	
	str = gxx::format("string {}", "world");
	dprln(str);
	
	str = gxx::format("rint {}", i);
	dprln(str);
	
	str = gxx::format("astring {}", world);
	dprln(str);
	
	str = gxx::format("pstring {}", world2);
	dprln(str);
	
	str = gxx::format("int {a}", "a"_a=42);
	dprln(str);
	
	str = gxx::format("string {a}", "a"_a=std::string("world"));
	dprln(str);
	
	str = gxx::format("rint {a}", "a"_a=i);
	dprln(str);
	
	str = gxx::format("astring {a}", "a"_a=world);
	dprln(str);
	
	str = gxx::format("pstring {a}", "a"_a=world2);
	dprln(str);
	
	fmtpr("pstring {a}\r\n", "a"_a=world2);
	
	//println("{0}", "Mirmik");	
	
	//println("What are you doing here, {who}, {uuu}", "who"_a="my darling", "uuu"_a="Another opinion is always fake.");
}