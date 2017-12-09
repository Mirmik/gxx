#include <gxx/print.h>
#include <gxx/geom/prim.h>
#include <gxx/math/vector.h>

namespace geom = gxx::geom3d;

int main() {
	//geom::Point v1(0,0,0);
	//geom::Point v2(1,1,1);
	//geom::Point v3(2,2,1);

	//geom::triangle tria(v1,v2,v3);

	//gxx::println(tria);


	//gxx::println(quick_rsqrt(1));

	//gxx::math::vector3 vec(2,1,1);
	//auto v = vec.quick_normalize();

	//std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;  
	//std::cout << v.x << ' ' << v.y << ' ' << v.z << std::endl;  
	auto pnt = geom::point(0,1,1);

	geom::line lin1(geom::point(0,0,0), geom::direction(1,1,0.1));
	geom::line lin2(geom::point(0,0,1.3), geom::direction(1,0,0));

	std::cout << lin1.distance(lin2) << std::endl;
}