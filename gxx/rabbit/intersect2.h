#ifndef GXX_RABBIT_INTERSET2_H
#define GXX_RABBIT_INTERSET2_H

#include <gxx/rabbit/topo2.h>
#include <algorithm>

namespace rabbit {
	using curve2 = gxx::geom2::curve;
	using interval = gxx::interval<double>;

	void curve_curve_intersection(const curve2&, const curve2&, std::vector<double>&, std::vector<double>&, const interval&, const interval&);

	class boolean_algorithm_2d {
		const face2& a;
		const face2& b;

		enum edge_classify : uint8_t {
			True,
			False,
			NotInfomation
		};

		class lvertex;
		class ledge {
		public:
			lvertex* vstart;
			lvertex* vfinish;

			const curve2* crv;
			double start;
			double finish;

			edge_classify aleft = NotInfomation;
			edge_classify aright = NotInfomation;
			edge_classify bleft = NotInfomation;
			edge_classify bright = NotInfomation;

			ledge(lvertex* s, lvertex* f, const trim2& tr, edge_classify al, edge_classify ar, edge_classify bl, edge_classify br) : 
				vstart(s), vfinish(f), crv(tr.crv.get()), start(tr.tstart), finish(tr.tfinish), aleft(al), aright(ar), bleft(bl), bright(br) {}
		
			ledge(lvertex* s, lvertex* f, const curve2* crv, double ts, double tf, edge_classify al, edge_classify ar, edge_classify bl, edge_classify br) : 
				vstart(s), vfinish(f), crv(crv), start(ts), finish(tf), aleft(al), aright(ar), bleft(bl), bright(br) {}
		};

		class lvertex {
		public:
			std::vector<ledge*> inedges;
			std::vector<ledge*> outedges;
		};

		std::map<const trim2*, std::vector<double>> apntsmap;
		std::map<const trim2*, std::vector<double>> bpntsmap;

		struct smallzone : public malgo2::vector2<double> {
			bool operator < (const malgo2::vector2<double>& pnt) const {
				return (x < (pnt.x - gxx::geom2::precision)) || (y < (pnt.y - gxx::geom2::precision));
			}
			smallzone(const malgo2::vector2<double>& oth) : malgo2::vector2<double>(oth) {}
		};

		std::map<smallzone, lvertex> locvtxs;
		std::vector<ledge> locedgs;

		bool evaluate_intersect_stage = false;

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
			evaluate_intersect_stage = true;
		}

		void generate_local_data() {
			assert(evaluate_intersect_stage);

			for (const loop2& l : a.loops) {	
				for (const trim2& t : l.edges) {
					std::vector<double>& intsvec = apntsmap[&t];
					if (!intsvec.empty()) {
						intsvec.push_back(t.tstart);
						intsvec.push_back(t.tfinish);
						std::sort(intsvec.begin(), intsvec.end());
						for (int i = 0; i < intsvec.size() - 1; ++i) {
							lvertex* vstart = &locvtxs[smallzone(t.crv->d0(intsvec[i]))];
							lvertex* vfinish = &locvtxs[smallzone(t.crv->d0(intsvec[i+1]))];
							if (vstart != vfinish) {
								locedgs.emplace_back(vstart, vfinish, t.crv.get(), intsvec[i], intsvec[i+1], True, False, NotInfomation, NotInfomation);
								ledge* e = &locedgs[locedgs.size() - 1]; 
								vfinish->inedges.push_back(e);
								vstart->outedges.push_back(e);
							}
						}
					} else {
						lvertex* vstart = &locvtxs[smallzone(t.start())];
						lvertex* vfinish = &locvtxs[smallzone(t.finish())];
						locedgs.emplace_back(vstart, vfinish, t, True, False, NotInfomation, NotInfomation);
					} 
				}
			}

			gxx::println(locedgs.size());
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