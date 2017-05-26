#include <iostream>
#include <gxx/string.h>

int main() {
	gxx::string str = "HelloWorld";
	std::cout << str.c_str() << std::endl;
}