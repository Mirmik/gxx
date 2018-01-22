#include <gxx/print.h>
#include <gxx/io/std.h>
#include <gxx/rabbit/topo2.h>
#include <gxx/rabbit/intersect2.h>
#include <gxx/rabbit/figure.h>
#include <gxx/rabbit/draw.h>

#include <gxx/x11wrap/shower2d.h>

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

	rabbit::point apnts[] = {
		{0, 0},
		{2, 0},
		{2, 2},
		{0, 2},
	};

	rabbit::point bpnts[] = {
		{0+1, 0+1},
		{2+1, 0+1},
		{2+1, 2+1},
		{0+1, 2+1},
	};

	rabbit::point cpnts[] = {
		{0+0.5, 0+0.5},
		{2+0.5, 0+0.5},
		{2+0.5, 2+0.5},
		{0+0.5, 2+0.5},
	};

	rabbit::point dpnts[] = {
		{-1, 0.8},
		{4, 0.8},
		{4, 0.9},
		{-1, 0.9},
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

	auto s1 = rabbit::figure::rectangle(20, 30);
	auto s2 = rabbit::figure::rectangle(30, 40).translate(10,10);

	gxx::shower2d sch;

	rabbit::draw(sch, s2);
	rabbit::draw(sch, s1);

	sch.exec();

	//rabbit::face2 aface(alp);
	//rabbit::face2 bface(blp);

	/*rabbit::boolean_algorithm_2d balgo(aface, bface);
	balgo.evaluate_intersection();
	balgo.print_intersection();

	balgo.generate_local_data();*/
}