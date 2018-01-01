#include <gxx/print.h>
#include <gxx/geom/geom2.h>
//#include <gxx/geom/curve2.h>

#include <gxx/x11wrap/shower2d.h>

namespace g2 = gxx::geom2;

int main() {
	g2::circle circ(60, g2::point(30,30), g2::direction(1,0));
	g2::circle circ2(60, g2::point(40,40), g2::direction(1,0));
	g2::line lin2(g2::point(-50,60), g2::point(80, 78));
	g2::line lin1(g2::point(-50,60), g2::point(140,120));

	auto res1 = lin1 ^ lin2;
	auto res2 = circ ^ lin1;
	auto res3 = circ ^ lin2;
	auto res4 = circ ^ circ2;
	
	//gxx::scene2d scn;

	//scn.add(pnt1);
	//scn.add(pnt2);

	//gxx::monitor mon(500, 500);
	//gxx::camera2d cam2d(0,0);

	//gxx::render2d(scn, cam2d, mon);

	//gxx::visio vis(mon);
	//vis.start();

	gxx::shower2d sch;
	//sch.add(pnt1);
	//sch.add(pnt2);


	sch.add_curve(circ);
	sch.add_curve(lin1);
	sch.add_curve(lin2);

	//sch.add_curve(gxx::geom2::line(g2::point(0,0), g2::direction(0,1)));
	//sch.add_curve(gxx::geom2::line(g2::point(0,0), g2::direction(1,0)));

	for (auto& a : res1.common.points) sch.add_point(a);
	for (auto& a : res2.common.points) sch.add_point(a);
	for (auto& a : res3.common.points) sch.add_point(a);

	sch.exec();
}