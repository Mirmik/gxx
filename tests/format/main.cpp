#include <iostream>
#include <map>
#include <gxx/print.h>
#include <gxx/print/stdprint.h>
#include <gxx/io/stdprintable.h>


using namespace gxx::argument_literal;
//using namespace gxx::print_funcs;

int main() {
	gxx::debug_ostream dout;
	dout.println(35);

	std::vector<int> vec;
	vec.emplace_back(3);
	vec.emplace_back(5);
	vec.emplace_back(6);
	vec.emplace_back(90);
	
	gxx::println(dout, vec);
	//gxx::fmtprintln(dout, vec);


	/*std::string str;

	str = gxx::format("int {}", 42);
	dprln(str);

	gxx::fmtprint("int {}", 43);

	gxx::print(385);
	gxx::println(987);
	gxx::println("HelloWorld");

	std::vector<int> vec;
	vec.emplace_back(3);
	vec.emplace_back(5);
	vec.emplace_back(6);
	vec.emplace_back(90);

	gxx::println(vec);

	std::map<std::string, int> m;
	m.insert(std::make_pair("Hello", 3));
	m.insert(std::make_pair("Hello2", 4));

	gxx::println(m);*/

/*	char world[] = "World";
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
	
	gxx::fmt::print("pstring {a}\r\n", "a"_a=world2);*/
}