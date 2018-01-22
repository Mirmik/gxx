#ifndef GXX_RABBIT_TOPO2_H
#define GXX_RABBIT_TOPO2_H

#include <memory>
#include <gxx/geom/geom2.h>
#include <gxx/math/interval.h>

namespace rabbit {
	using interval = gxx::math::interval<double>;
	using directed_interval = gxx::math::directed_interval<double>;
	using curve2 = gxx::geom2::curve;
	using point = gxx::geom2::point;
	using point2 = gxx::geom2::point;
	using vector2 = malgo::vector2<double>;

	//Трим - это часть кривой, имеющая направление и ограничения
	struct trim2 {
		std::shared_ptr<curve2> crv;
		directed_interval tparam;

		trim2() = default;
		trim2(gxx::geom2::curve* crv, directed_interval t) : crv(crv), tparam(t) {}
		trim2(std::shared_ptr<curve2> crv, directed_interval t) : crv(crv), tparam(t) {}
		trim2(gxx::geom2::curve* crv, double s, double f) : crv(crv), tparam(s, f) {}
		trim2(std::shared_ptr<curve2> crv, double s, double f) : crv(crv), tparam(s, f) {}
		trim2(const trim2& tr, double s, double f) : crv(tr.crv), tparam(tr.tparam.proc(s), tr.tparam.proc(f)) {}

		point finish() const { return crv->d0(tparam.finish()); }
		point start() const { return crv->d0(tparam.start()); }

		point d0(double prc) const {
			return crv->d0(tparam.proc(prc));
		}

		vector2 d1(double prc) const {
			auto tmp = crv->d1(tparam.proc(prc));
			return tparam.reverse ? -tmp : tmp;
		}

		trim2 translate(double x, double y) const {
			return trim2(crv->translate(x,y), tparam);
		}

		size_t printTo(gxx::io::ostream& o) const {
			return gxx::print_to(o, *crv, tparam);
		}
	};

	struct loop2 {
		std::vector<trim2> edges;
		loop2(){}
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

		size_t printTo(gxx::io::ostream& o) const {
			return gxx::println(edges);
		}

		loop2 translate(double x, double y) const {
			loop2 ret;
			for (const trim2& t : edges) {
				ret.edges.push_back(t.translate(x,y));
			}
			return ret;
		}
	};

	struct face2 {
		/*std::vector<loop2> loops;
		face2(const std::initializer_list<loop2>& lst) : loops(lst.begin(), lst.end()) {}
		face2(const loop2& lp) { loops.push_back(lp); }*/
	};

	struct line2 : public trim2 {
		line2(point a, point b) : trim2(new gxx::geom2::line(a, b-a), 0, (b-a).abs()) {}
	};
}

#endif