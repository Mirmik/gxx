#ifndef GXX_RABBIT_INTERSET2_H
#define GXX_RABBIT_INTERSET2_H

#include <gxx/rabbit/topo2.h>

namespace rabbit {
	using curve2 = gxx::geom2::curve;
	using interval = gxx::interval<double>;

	void curve_curve_intersection(const curve2&, const curve2&, std::vector<double>&, std::vector<double>&, const interval&, const interval&);

	class trim_intersection_algorithm {
		const trim2& a;
		const trim2& b;

	public:
		std::vector<double> apoints;
		std::vector<double> bpoints;

	public:
		trim_intersection_algorithm(const trim2& a, const trim2& b) : a(a), b(b) {}
	
		void doit() {
			curve_curve_intersection(*a.crv, *b.crv, apoints, bpoints, a.interval(), b.interval());
		}

		bool empty() {
			assert(apoints.empty() == bpoints.empty());
			return apoints.empty();
		}
	};

	class loop_intersection_algorithm {
		const loop2& a;
		const loop2& b;

		std::map<const trim2*, std::vector<double>> apntsmap;
		std::map<const trim2*, std::vector<double>> bpntsmap;

	public:
		loop_intersection_algorithm(const loop2& a, const loop2& b) : a(a), b(b) {}
	
		void doit() {
			for (const trim2& at : a.edges) {
				for (const trim2& bt : b.edges) {
					trim_intersection_algorithm trmint(at, bt);
					trmint.doit();

					//gxx::println("trim intersection");
					//gxx::println("a:", trmint.apoints);
					//gxx::println("b:", trmint.bpoints);

					if (!trmint.empty()) {
						//gxx::println("add");
						apntsmap[&at].insert(apntsmap[&at].end(), trmint.apoints.begin(), trmint.apoints.end());
						bpntsmap[&bt].insert(bpntsmap[&bt].end(), trmint.bpoints.begin(), trmint.bpoints.end());
					}
				}	
			}

			gxx::println(apntsmap);
			gxx::println(bpntsmap);

			for (auto p : apntsmap) {
				for (auto v : p.second) {
					gxx::println(p.first->crv->d0(v));
				}
			}
		}
	};

}

#endif