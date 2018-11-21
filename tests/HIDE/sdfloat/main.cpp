#include <gxx/util/math.h>
#include <gxx/print.h>

int main() {
	gxx::println(isint(8.96));
	gxx::println(isint(8.05));
	gxx::println(isint(800000096));
	gxx::println(isint(80));
	gxx::println(isint(8));
	gxx::println(isint(8.0));
}