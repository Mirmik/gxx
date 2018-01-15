#ifndef GXX_RABBIT_TOPO2_H
#define GXX_RABBIT_TOPO2_H

#include <memory>
#include <gxx/geom/geom2.h>
#include <gxx/util/interval.h>

namespace rabbit {
	using point = gxx::geom2::point;

	//Трим - это часть кривой, имеющая направление и ограничения
	struct trim2 {
		double tstart;
		double tfinish;
		std::shared_ptr<gxx::geom2::curve> crv;

		trim2(gxx::geom2::curve* crv, double s, double f) : crv(crv), tstart(s), tfinish(f) {}
		point finish() const { return crv->d0(tfinish); }
		point start() const { return crv->d0(tstart); }
		gxx::interval<double> interval() const { return gxx::interval<double>(tstart, tfinish); }
	};

	struct loop2 {
		std::vector<trim2> edges;
		loop2(const std::initializer_list<trim2>& lst) : edges(lst.begin(), lst.end()) {}
		loop2(std::vector<trim2>&& oth) : edges(std::move(oth)) {}
		bool check_closed() const {
			point last = edges[edges.size()-1].finish();
			for (const auto& t: edges) {
				if (t.start().is_not_same(last)) return false;
				last = t.finish();
			}
			return true;
		}
	};

	struct face2 {
		std::vector<std::shared_ptr<loop2>> loops;
		face2(const std::initializer_list<std::shared_ptr<loop2>>& lst) : loops(lst.begin(), lst.end()) {}
	};

	struct line2 : public trim2 {
		line2(point a, point b) : trim2(new gxx::geom2::line(a, b-a), 0, (b-a).abs()) {}
	};
}

#endif