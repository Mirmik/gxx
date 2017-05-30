#include <iostream>
#include <gxx/format.h>

using namespace gxx::literals;

int main() {
	gxx::string str;
	const char* world = "world";

	const char* fmt = "Hello, {0:U}!";
	str = gxx::format(fmt, "world");
	std::cout << str.c_str() << std::endl;

	/*const char* fmt6 = "Hello, {0}!";
	str = gxx::format(fmt6, 324);
	std::cout << str.c_str() << std::endl;

	const char* fmt2 = "Hello, {1:U}! Number is, {kekeke:15>}!";
	str = gxx::format(fmt2, 16*15, "world", "kekeke"_a=34);
	std::cout << str.c_str() << std::endl;

	str = gxx::format("Hello, {1:U}! Number is {75:pX}, {kekeke:15>}!", 16*15, world, "kekeke"_a=34);
	std::cout << str.c_str() << std::endl;*/
}