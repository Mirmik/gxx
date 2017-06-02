#include <iostream>
#include <gxx/string.h>
#include <gxx/debug/dprint.h>

using namespace gxx::string_literal;

int main() {
	gxx::string str = "HelloWorld"_gs;
	dprln(str);

	gxx::string a = "mirmik"_gs;
	gxx::string b = "mir"_gs;

	dprln(a < b);
	dprln(a > b);
}