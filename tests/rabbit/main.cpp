#include <gxx/print.h>
#include <gxx/io/std.h>
#include <gxx/rabbit/topo2.h>
#include <gxx/rabbit/intersect2.h>

int main() {

	/*rabbit::line2 lna(rabbit::point2(0,1), rabbit::point2(1,1));
	rabbit::line2 lnb(rabbit::point2(1,0), rabbit::point2(1,1));
	GXX_PRINT(trim_trim_intersection(lna, lnb));

	rabbit::line2 ln1(rabbit::point2(-1,-1), rabbit::point2(1,1));
	rabbit::line2 ln2(rabbit::point2(-1,1), rabbit::point2(1,-1));
	rabbit::line2 ln3(rabbit::point2(0,0), rabbit::point2(2,-2));
	rabbit::line2 ln4(rabbit::point2(2,2), rabbit::point2(0,0));

	GXX_PRINT(trim_trim_intersection(ln1, ln2));
	GXX_PRINT(trim_trim_intersection(ln1, ln1));
	GXX_PRINT(trim_trim_intersection(ln2, ln2));
	GXX_PRINT(trim_trim_intersection(ln2, ln3));
	GXX_PRINT(trim_trim_intersection(ln2, ln4));
	GXX_PRINT(trim_trim_intersection(ln4, ln2));

	auto res = trim_trim_intersection(ln2, ln3);
	if (res.is_interval()) {
		GXX_PRINT(ln2.crv->d0(res.aint.minimum));
		GXX_PRINT(ln2.crv->d0(res.aint.maximum));
		GXX_PRINT(ln3.crv->d0(res.bint.minimum));
		GXX_PRINT(ln3.crv->d0(res.bint.maximum));
	}

	rabbit::line2 bln0(rabbit::point2(0,0), rabbit::point2(1,1));
	rabbit::line2 bln1(rabbit::point2(1,1), rabbit::point2(0,0));
	GXX_PRINT(trim_trim_intersection(bln0, bln1));*/

	//gxx::println("HelloWorld");

	rabbit::point apnts[3] = {
		{0, 0},
		{0, 1},
		{1, 0}
	};

	rabbit::point bpnts[3] = {
		{0+0.2, 0+0.2},
		{0+0.2, 1+0.2},
		{1+0.2, 0+0.2}
	};

	/*rabbit::point bpnts[3] = {
		{0, 0},
		{0, 1},
		{1, 0}
	};*/

	/*rabbit::point bpnts[3] = {
		{0 + 1, 0},
		{0 + 1, 1},
		{1 + 1, 0}
	};*/


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

	gxx::println(loop_loop_intersection(alp, blp));

	//rabbit::face2 aface(alp);
	//rabbit::face2 bface(blp);

	/*rabbit::boolean_algorithm_2d balgo(aface, bface);
	balgo.evaluate_intersection();
	balgo.print_intersection();

	balgo.generate_local_data();*/
}