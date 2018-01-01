#include <gxx/print.h>
#include <gxx/geom/geom2.h>
//#include <gxx/geom/curve2.h>

#include <gxx/x11wrap/shower2d.h>

namespace g2 = gxx::geom2;

int main() {
	g2::point pnt1(0,0);
	g2::point pnt2(3,9);
	g2::direction dir1(1,1);
	g2::direction dir2(1,0);

//	g2::line l1(pnt1, dir1);
	
	//auto res = g2::intersect_curve2_curve2(l1, l2);



//	gxx::println(l1.distance(pnt2));

	g2::circle circ(6, g2::point(3,3), g2::direction(1,0));
	g2::line lin2(pnt2, dir2);
	g2::line lin1(pnt1, dir1);

	auto res = g2::intersect_curve2_curve2(circ, lin2);
	gxx::println(res.first);
	gxx::println(res.second);

	auto res2 = g2::intersect_curve2_curve2(lin2, lin1);
	gxx::println(res2.first);
	gxx::println(res2.second);

	//gxx::scene2d scn;

	//scn.add(pnt1);
	//scn.add(pnt2);

	//gxx::monitor mon(500, 500);
	//gxx::camera2d cam2d(0,0);

	//gxx::render2d(scn, cam2d, mon);

	//gxx::visio vis(mon);
	//vis.start();

	gxx::shower2d sch;
	sch.add(pnt1);
	sch.add(pnt2);

	sch.exec();
}