#include <gxx/print.h>
#include <gxx/geom/prim.h>
#include <gxx/math/vector.h>

namespace geom = gxx::geom3d;

int main() {
	//gxx::println(quick_rsqrt(1));

	//gxx::math::vector3 vec(2,1,1);
	//auto v = vec.quick_normalize();

	//std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;  
	//std::cout << v.x << ' ' << v.y << ' ' << v.z << std::endl;  
	auto pnt = geom::point(0,1,1);

	geom::line lin1(geom::point(0,0,0), geom::direction(1,1,0.1));
	geom::line lin2(geom::point(0,0,1.3), geom::direction(1,0,0));

	gxx::print(float(0));
	//std::cout << lin1.distance(lin2) << std::endl;
}