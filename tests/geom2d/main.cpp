#include <gxx/print.h>
#include <gxx/geom/geom2.h>
//#include <gxx/geom/curve2.h>

namespace g2 = gxx::geom2;

int main() {
	g2::point pnt1(0,0);
	g2::point pnt2(0,1);
	g2::direction dir1(0,1);
	g2::direction dir2(0,1);

	g2::line l1(pnt1, dir1);
	g2::line l2(pnt2, dir2);
	
	auto res = g2::intersect_curve2_curve2(l1, l2);

	gxx::println(res);
}