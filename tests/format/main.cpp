#include <iostream>
#include <map>
#include <gxx/print.h>
#include <gxx/print/stdprint.h>
#include <gxx/io/stdprintable.h>
#include <gxx/serialize/trent.h>

class A : public gxx::io::printable {
public:
	int i = 42;

	size_t printTo(gxx::io::ostream& o) const override {
		return gxx::fprint(o, "A({})", i);
	}
};

int main() {
	gxx::debug_ostream dout;
	dout.println(35);

	std::vector<std::vector<int>> vec;
	vec.emplace_back(std::vector<int>{7,9,0});
	vec.emplace_back(std::vector<int>{7,9,1});
	vec.emplace_back(std::vector<int>{7,2,0});
	vec.emplace_back(std::vector<int>{7,9,0});
	
	gxx::println(vec);
	gxx::fprintln("{}, Hello, {}, {}", vec, A(), "Mirmik");

	gxx::trent tr;

	tr[0] = 24;
	tr[1] = 21;
	tr[2]["mirmik"] = std::string("Hello");

	gxx::println(tr);
}