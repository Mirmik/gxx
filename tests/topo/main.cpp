#include <gxx/print.h>
#include <gxx/geom/topo.h>

int main() {
	//gxx::topo::cube(3);

	gxx::geom3::point a = gxx::geom3::point(0,0,0);
	gxx::geom3::point b = gxx::geom3::point(1,0,0);
	gxx::geom3::point c = gxx::geom3::point(0,1,0);
	gxx::geom3::point d = gxx::geom3::point(0,0,1);

	gxx::topo::edge edg0(a,b);
	gxx::topo::edge edg1(b,c);
	gxx::topo::edge edg2(c,a);
	gxx::topo::edge edg3(d,a);
	gxx::topo::edge edg4(d,b);
	gxx::topo::edge edg5(d,c);

	gxx::topo::wire wr0 {edg0, edg1, edg2};
	gxx::topo::wire wr1 {edg0, edg4, edg3};
	gxx::topo::wire wr2 {edg2, edg5, edg3};
	gxx::topo::wire wr3 {edg1, edg5, edg4};

	gxx::topo::face f0(wr0);
/*
	//auto s = wr0.list_of_vertex();
	//for (auto& r : s) {
	//	gxx::println(*r);
	//}

	/*auto wr1 = gxx::topo::multiline( std::vector<gxx::geom3::point>{ a, b, c }, true );
	auto fc = new gxx::topo::face(wr1);
*/
	/*gxx::topo::shell shl { 
		gxx::topo::face(wr0), 
		gxx::topo::face(wr1), 
		gxx::topo::face(wr2), 
		gxx::topo::face(wr3) 
	};*/
}