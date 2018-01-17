#include <gxx/print.h>
#include <gxx/io/std.h>
#include <gxx/rabbit/topo2.h>
#include <gxx/rabbit/intersect2.h>

int main() {
	//gxx::println("HelloWorld");

	rabbit::point apnts[3] = {
		{0, 0},
		{0, 1},
		{1, 0}
	};

	rabbit::point bpnts[3] = {
		{0, 0+0.5},
		{0, 1+0.5},
		{1, 0+0.5}
	};

	rabbit::loop2 alp {
		rabbit::line2(apnts[0], apnts[1]),
		rabbit::line2(apnts[1], apnts[2]),
		rabbit::line2(apnts[2], apnts[0])
	};

	rabbit::loop2 blp {
		rabbit::line2(bpnts[0], bpnts[1]),
		rabbit::line2(bpnts[1], bpnts[2]),
		rabbit::line2(bpnts[2], bpnts[0])
	};

	rabbit::face2 aface(alp);
	rabbit::face2 bface(blp);

	rabbit::boolean_algorithm_2d balgo(aface, bface);
	balgo.evaluate_intersection();

	balgo.print_intersection();
}