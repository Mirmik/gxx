#include <iostream>
#include <map>
#include <string>
#include <gxx/print.h>
#include <gxx/print/stdprint.h>

using namespace gxx::argument_literal;

/*class A {
public:
	A() {
		std::cout << "std::hel2lo" << std::endl;
		gxx::println("Hello"); // valid if have priority initialization
	}
} a;*/

int main() {
	dprptrln(&std::cout);
	dprptrln(gxx::standart_output);

	gxx::println(1);
	gxx::fprintln("{}", 1);
	gxx::fprintln("{}", "hello");
	gxx::fprintln("{a}", "a"_a=1);
	gxx::fprintln("{b}, {c}", "b"_a="hello", "c"_a=std::string("fdsafasd"));

	const char* hello = "HelloWorld";

	//gxx::print_dump(hello, 10);


//	std::map<std::string, int> mp;

//	mp.insert(std::make_pair(std::string("Hello"), 2));
//	mp.insert(std::make_pair(std::string("Hello2"), 3));

//	gxx::fprintln("{}", mp);
}