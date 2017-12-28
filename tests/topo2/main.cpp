#include <gxx/print.h>
#include <gxx/geom/topo2.h>
#include <gxx/geom/prim2.h>

namespace g2 = gxx::geom2;
namespace t2 = gxx::topo2;
namespace prim2 = gxx::topo2::prim;

int main() {
	prim2::triangle(g2::point(0,0), g2::point(10,0), g2::point(0,10));
}