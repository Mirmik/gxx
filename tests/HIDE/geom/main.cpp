#include <gxx/print.h>
#include <gxx/geom/geom3.h>

namespace geom3 = gxx::geom3;

int main() {
	geom3::curve crv(geom3::point(0,0,1), geom3::point(1,2,3));
	gxx::println(crv);
}