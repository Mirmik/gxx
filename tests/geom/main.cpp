#include <gxx/print.h>
#include <gxx/geom/geom3.h>
#include <gxx/geom/curve3.h>
#include <gxx/geom/surface3.h>

namespace geom = gxx::geom3;

int main() {
	auto m3 = malgo3::matrix3<double>::zx_rotation(0,0);
	auto v3 = malgo3::vector3<double>{2,3,4};

	gxx::println(m3 * v3);
}