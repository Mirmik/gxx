#include <gxx/rabbit/topo2.h>
#include <gxx/rabbit/intersect2.h>
#include <gxx/rabbit/figure.h>
#include <gxx/rabbit/draw.h>

#include <gxx/x11wrap/shower2d.h>

//#include <iterator>

rabbit::loop2 make_liter(const std::vector<rabbit::point>& pnts) {
	std::pair<rabbit::loop2, rabbit::loop2> lp;
	lp.first = rabbit::figure::bline(pnts[0],pnts[1], 8);
	for (int i = 1; i < pnts.size() - 1; ++i) {
		auto b = rabbit::figure::bline(pnts[i],pnts[i+1], 8);
		lp = rabbit::loop_loop_combine(lp.first, b);
	}
	return lp.first;
}

int main() {
	double t = 100;
	double tr = 140;

	std::vector<rabbit::point> Mpnts = {
		{0,0},
		{0,t},
		{t/2,0},
		{t,t},
		{t,0},
	};

	std::vector<rabbit::point> Ipnts = {
		{t/2,0},
		{t/2,t},
	};

	std::vector<rabbit::point> Rpnts = {
		{0,0},
		{0,t},
		{t,t*7/8},
		{t/2,t/2},
		//{t/2,t/2},
		{t,0},
	};

	std::vector<rabbit::point> Kpnts = {
		{0,0},
		{0,t},
		{t/8,t/2},
		{t,t},
		{t/4,t/2},
		{t,0},
	};

	gxx::shower2d sch;
	sch.update_window(1000,400);
	rabbit::draw(sch, make_liter(Mpnts).translate(-tr*3 -t/2 + tr/2, -t/2));
	rabbit::draw(sch, make_liter(Ipnts).translate(-tr*2 -t/2 + tr/2, -t/2));
	rabbit::draw(sch, make_liter(Rpnts).translate(-tr*1 -t/2 + tr/2, -t/2));
	rabbit::draw(sch, make_liter(Mpnts).translate(tr*0 -t/2 + tr/2, -t/2));
	rabbit::draw(sch, make_liter(Ipnts).translate(tr*1 -t/2 + tr/2, -t/2));
	rabbit::draw(sch, make_liter(Kpnts).translate(tr*2 -t/2 + tr/2, -t/2));

	sch.exec();
}