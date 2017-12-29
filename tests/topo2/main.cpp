#include <gxx/print.h>
#include <gxx/geom/topo2.h>
#include <gxx/geom/prim2.h>

namespace g2 = gxx::geom2;
namespace t2 = gxx::topo2;
namespace prim2 = gxx::topo2::prim;

int main() {
	//prim2::triangle(g2::point(0,0), g2::point(10,0), g2::point(0,10));
	//prim2::square(33);

	auto tr1 = prim2::triangle(g2::point(0,0), g2::point(3,0), g2::point(0,3));
	auto tr2 = prim2::triangle(g2::point(1,1), g2::point(4,1), g2::point(1,4));

	t2::fuse(tr1, tr2);
	
}