#include <gxx/json.h>
#include <iostream>
#include <sstream>

int main() {
	gxx::json js;

	std::string str = "{ 'a': 3 }";
	std::stringstream sstr(str);

	js.parse(sstr);

	js.printTo(std::cout);
}