#include <gxx/print.h>
#include <gxx/geom/geom2.h>
//#include <gxx/geom/curve2.h>

namespace g2 = gxx::geom2;

int main() {
//	g2::point pnt1(0,0);
	g2::point pnt2(3,3);
//	g2::direction dir1(1,1);
	g2::direction dir2(1,0);

//	g2::line l1(pnt1, dir1);
	
	//auto res = g2::intersect_curve2_curve2(l1, l2);



//	gxx::println(l1.distance(pnt2));

	g2::circle circ(6, g2::point(3,3), g2::direction(1,0));
	g2::line lin(pnt2, dir2);

	auto res = g2::intersect_curve2_curve2(circ, lin);
	gxx::println(res.first);
	gxx::println(res.second);

	for(auto& e : res.first.points) {
		gxx::println(circ.d0(e));
	}

	for(auto& e : res.second.points) {
		gxx::println(lin.d0(e));
	}
}