#include <iostream>
#include <gxx/format.h>

using namespace gxx::literals;

int main() {
	
	gxx::string str = gxx::format("Hello, {1:U}! Number is {0:pX}, {kekeke:15>}!", 16*15, "world", "kekeke"_a=34);
	std::cout << str.c_str() << std::endl;
}