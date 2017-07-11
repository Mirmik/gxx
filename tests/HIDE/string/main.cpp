#include <iostream>
#include <gxx/string.h>
#include <gxx/debug/dprint.h>

#include <map>

using namespace gxx::string_literal;

int main() {
	gxx::string str = "HelloWorld"_gs;
	dprln(str);

	gxx::string a = "mirmik"_gs;
	gxx::string b = "mirmik"_gs;

	dprln(a < b);
	dprln(b < a);

	std::map<gxx::string, gxx::string> m;

	m.insert(std::make_pair("gs"_gs, "mirmk"_gs));
	m.insert(std::make_pair("gs2"_gs, "mirmk2"_gs));
	dprln(m["gs"_gs]);
	dprln(m["gs2"_gs]);
	dprln(m["gs"_gs]);
	dprln(m["gs2"_gs]);
}