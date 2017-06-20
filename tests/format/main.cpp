#include <iostream>
#include <gxx/format.h>

using namespace gxx::arglist_literal;

int main() {
	char world[128] = "World";
	const char* world2 = "World";
	int i = 456;

	gxx::string str;

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

	str = gxx::format("string {a}", "a"_a="world");
	dprln(str);

	str = gxx::format("rint {a}", "a"_a=i);
	dprln(str);

	str = gxx::format("astring {a}", "a"_a=world);
	dprln(str);

	str = gxx::format("pstring {a}", "a"_a=world2);
	dprln(str);
}