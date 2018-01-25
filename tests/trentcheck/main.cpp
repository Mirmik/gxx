#include <gxx/trent/trent_checker.h>

int main() {
	
	gxx::schema checker = gxx::schema::dict({
		{ "mirmik", gxx::schema::list().length(2) },
		{ "mirmik2", gxx::schema::string() },
	});

	gxx::trent tr;
	tr["mirmik"][0] = 28;
	tr["mirmik"][1] = 33;
	tr["mirmik2"] = std::string("mirmik");

	checker.asserted_check(tr, "mirmiktrent");
}