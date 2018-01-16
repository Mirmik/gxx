#ifndef GXX_RABBIT_INTERSET2_H
#define GXX_RABBIT_INTERSET2_H

#include <gxx/rabbit/topo2.h>

namespace rabbit {
	using curve2 = gxx::geom2::curve;
	using interval = gxx::interval<double>;

	void curve_curve_intersection(const curve2&, const curve2&, std::vector<double>&, std::vector<double>&, const interval&, const interval&);

	class boolean_algorithm_2d {
		const face2& a;
		const face2& b;

		std::map<const trim2*, std::vector<double>> apntsmap;
		std::map<const trim2*, std::vector<double>> bpntsmap;

	public:
		boolean_algorithm_2d(const face2& a, const face2& b) : a(a), b(b) {}
	
		void evaluate_intersection() {
			for (const loop2& al : a.loops) {
				for (const loop2& bl : b.loops) {
					for (const trim2& at : al.edges) {
						for (const trim2& bt : bl.edges) {
							auto& apoints = apntsmap[&at];
							auto& bpoints = bpntsmap[&bt];
							curve_curve_intersection(*at.crv, *bt.crv, apoints, bpoints, at.interval(), bt.interval());
						}
					}
				}	
			}
		}

		void print_intersection() {
			gxx::println("ALOOP:");
			for (auto p : apntsmap) {
				gxx::println(*p.first->crv);
				for (auto v : p.second) {
					gxx::fprintln("\t{} -> {}", v, p.first->crv->d0(v));
				}
			}

			gxx::println("BLOOP:");
			for (auto p : bpntsmap) {
				gxx::println(*p.first->crv);
				for (auto v : p.second) {
					gxx::fprintln("\t{} -> {}", v, p.first->crv->d0(v));
				}
			}
		}
	};

}

#endif