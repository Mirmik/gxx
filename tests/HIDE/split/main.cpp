#include <gxx/format.h>

int main() {
	auto spl = gxx::split("abra kadabra 2fgg", ' ');

	for (auto s : spl) {
		dprf("str: {}\r\n", s.c_str());
		dprf("size: {}\r\n", s.size());
	}

	dprln(spl.size());
}