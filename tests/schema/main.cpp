#include <gxx/print.h>
#include <gxx/trent/schema.h>

auto sch = gxx::schema::numer();

//gxx::trent tr(gxx::trent::type::dict);
gxx::trent tr = 5;

int main() {
	sch.check(tr);
}