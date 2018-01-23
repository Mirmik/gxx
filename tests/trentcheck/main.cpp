#include <gxx/trent/trent_checker.h>

int main() {
	
	gxx::schema checker = gxx::schema::dict({
		{ "mirmik", gxx::schema::array() },
		{ "mirmik2", gxx::schema::string() },
	});

	gxx::trent tr;

	checker.check(tr);
}