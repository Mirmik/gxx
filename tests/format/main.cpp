#include <iostream>
#include <gxx/format.h>

int main() {
	
	gxx::string str = gxx::format("Hello, {1:U}! Number is {0:pX}!", 16*15, "world");
	std::cout << str.c_str() << std::endl;
}