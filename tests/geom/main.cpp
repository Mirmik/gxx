#include <gxx/print.h>
#include <gxx/geom/prim.h>
#include <gxx/math/vector.h>

//namespace geom = gxx::geom;

int main() {
	//geom::Point v1(0,0,0);
	//geom::Point v2(1,1,1);
	//geom::Point v3(2,2,1);

	//geom::triangle tria(v1,v2,v3);

	//gxx::println(tria);


	gxx::println(quick_rsqrt(1));

	gxx::math::vector3 vec(2,1,1);

	auto v = vec.quick_normalize();

	std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;  
	std::cout << v.x << ' ' << v.y << ' ' << v.z << std::endl;  

}