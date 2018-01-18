#include <iostream>
#include <map>
#include <string>
#include <gxx/print.h>
#include <gxx/print/stdprint.h>

class A {
public:
	A() {
		std::cout << "std::hel2lo" << std::endl;
		gxx::println("Hello"); // valid if have priority initialization
	}
} a;

int main() {
		dprptrln(&std::cout);
		dprptrln(gxx::standart_output);

	std::map<std::string, int> mp;

	mp.insert(std::make_pair(std::string("Hello"), 2));
	mp.insert(std::make_pair(std::string("Hello2"), 3));

	gxx::fprintln("{}", mp);
}