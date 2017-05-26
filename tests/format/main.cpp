#include <iostream>
#include <gxx/format.h>

int main() {
	
	gxx::string str = gxx::format("Hello, {1:U30}! Number is {0} !", 3, "world");

	std::cout << str.c_str() << std::endl;
}