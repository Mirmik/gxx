#include <gxx/print.h>
#include <gxx/geom/topo2.h>
#include <gxx/geom/prim2.h>

#include <gxx/x11wrap/shower2d.h>

namespace g2 = gxx::geom2;
namespace t2 = gxx::topo2;
//namespace prim2 = gxx::topo2::prim;

int main() {
	std::vector<g2::point> pnts {
		{0,10},
		{0,20},
		{10,10},
	};

	figure f;
	auto& w = f.add_wire();
	w.add_edge(pnts[0], pnts[1]);
	w.add_edge(pnts[1], pnts[2]);
	w.add_edge(pnts[2], pnts[0]);



	w.check();

	//t2::curve c1(pnts[0], pnts[1]);
	//t2::curve c2(pnts[1], pnts[2]);
	//t2::curve c3(pnts[2], pnts[0]);

	//auto l1 = new g2::line(pnts[0], pnts[1]);
	//auto l2 = new g2::line(pnts[1], pnts[2]);
	//auto l3 = new g2::line(pnts[2], pnts[0]);

	//auto w1 = new t2::wire {l1,l2,l3};
	//auto f1 = new t2::figure(w1);

	//prim2::triangle(g2::point(0,0), g2::point(10,0), g2::point(0,10));
	//prim2::square(33);
/*
	auto tr1 = prim2::triangle(g2::point(0,0), g2::point(30,0), g2::point(0,30));
	auto tr2 = prim2::triangle(g2::point(10,10), g2::point(40,10), g2::point(10,40));

	gxx::shower2d shr;
	
	for (auto ptr : tr1.conts[0].list_of_vertex()) {
		gxx::println("H");
		gxx::vprintln(ptr->next, ptr->prev);
		gxx::println(*ptr->next);
	}

	for (auto& s: tr1.conts[0].segs) {
		gxx::vprintln(s.v1.impl.get(), s.v2.impl.get());
		gxx::println(s.crv.get());
	}/*
 
	auto& seg = tr1.conts[0].segs[0];
	gxx::println(seg);
	gxx::println(seg.next());
	gxx::println(seg.next().next());

	shr.add_figure(tr1);
	shr.add_figure(tr2);
	
	shr.exec();*/

	//t2::fuse(tr1, tr2);
	
}