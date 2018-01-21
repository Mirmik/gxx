#include <gxx/rabbit/intersect2.h>
#include <typeinfo>
#include <typeindex>
#include <map>

namespace rabbit {	
	struct crvcrv_analytic_intresult {
		std::vector<double> apnts;
		std::vector<double> bpnts;
		std::vector<point2> pnts;
		bool same = false;
		
		double offset;
		bool revdir;

		bool have_points() const {
			return !apnts.empty(); 
		}	

		crvcrv_analytic_intresult(bool b) : same(b) {} 
		crvcrv_analytic_intresult(bool b, double offset, bool revdir) : same(b), offset(offset), revdir(revdir) {} 
		crvcrv_analytic_intresult(const std::initializer_list<double>& ap, const std::initializer_list<double>& bp, const std::initializer_list<point2>& p) : apnts(ap), bpnts(bp), pnts(p) {}
	
		crvcrv_analytic_intresult& swap_curves() {
			std::swap(apnts, bpnts);
			return *this;
		}

		bool empty() {
			return apnts.empty() && bpnts.empty() && same == false;
		}

		size_t printTo(gxx::io::ostream& o) const {
			if (have_points()) {
				gxx::fprint_to(o, "pnts:(a:{}, b:{}, r:{}) ", apnts, bpnts, pnts);
			}
			if (same) {
				gxx::fprint_to(o, "same curve -> off:{} rev:{}", offset, revdir);
			}

			return 1;
		}
	};

	using analytic_intsignature = crvcrv_analytic_intresult(*)(const curve2&, const curve2&); 	

	crvcrv_analytic_intresult line_line_intersection(const curve2& acrv, const curve2& bcrv) {
		const auto& a = static_cast<const gxx::geom2::line&>(acrv);
		const auto& b = static_cast<const gxx::geom2::line&>(bcrv);

		point l12 = a.l - b.l;
		double dd = a.d.crossmul(b.d);

		if (gxx::math::early_zero(dd, rabbit::precision)) {
			if (l12.early_zero() || gxx::math::is_same(l12.x / a.d.x, l12.y / a.d.y, rabbit::precision)) {
				return crvcrv_analytic_intresult(true, l12.sclmul(b.d), a.d.is_not_same(b.d));
			}
			else {
				return crvcrv_analytic_intresult(false);
			}
		}
		
		double t1 = b.d.crossmul(l12) / dd;
		double t2 = a.d.crossmul(l12) / dd;

		auto apnt = acrv.d0(t1);
		auto bpnt = bcrv.d0(t2);
		assert(apnt.is_same(bpnt));
		
		return crvcrv_analytic_intresult({t1}, {t2}, {apnt});
	}

	std::map<std::pair<std::type_index, std::type_index>, analytic_intsignature> intsmap {
		{std::pair<std::type_index, std::type_index>(typeid(gxx::geom2::line), typeid(gxx::geom2::line)), line_line_intersection}, 
	};

	crvcrv_analytic_intresult analytic_curve_curve_intersection(const curve2& acrv, const curve2& bcrv) {
		std::type_index atype = typeid(acrv); 
		std::type_index btype = typeid(bcrv);

		auto it = intsmap.find(std::pair<std::type_index, std::type_index>(atype, btype));
		if (it != intsmap.end()) { return it->second(acrv, bcrv); } 

		it = intsmap.find(std::pair<std::type_index, std::type_index>(btype, atype));
		if (it != intsmap.end()) { return it->second(bcrv, acrv).swap_curves(); }
	}

	trim_trim_intersection_result trim_trim_intersection(const trim2& a, const trim2& b) {
		trim_trim_intersection_result res;

		if (a.crv->is_analityc() && b.crv->is_analityc()) {
			//Пересечение кривых аналитического класса.
			auto crvres = analytic_curve_curve_intersection(*a.crv, *b.crv);
			
			if (crvres.empty()) return res;
			if (crvres.same) {
				//Кривые совпадают.
				//Ищем интервал B в системе координат A.
				auto bint_asystem = b.tparam.offset(crvres.offset);
				if (crvres.revdir) bint_asystem = bint_asystem.reverse();
				
				auto intersect = a.tparam.simple_intersect(bint_asystem);
				if (intersect) {
					res.aint = intersect;

					//Обратное преобразование.
					res.bint = crvres.revdir ? intersect.reverse() : intersect;
					res.bint = res.bint.offset( crvres.offset );
					res.trm = trim2(a.crv, res.aint.minimum, res.aint.maximum); 

					//ASSERTATION
					auto trm2 = trim2(b.crv, res.bint.minimum, res.bint.maximum); 
					if (!crvres.revdir) {
						assert(trm2.start().is_same(res.trm.start()));
						assert(trm2.finish().is_same(res.trm.finish()));
					} else {
						assert(trm2.start().is_same(res.trm.finish()));
						assert(trm2.finish().is_same(res.trm.start()));						
					}
				}
			} else {
				//Копируем точки пересечения.
				size_t sz = crvres.pnts.size();
				res.ipnts.reserve(sz);

				for (int i = 0; i < sz; ++i) {
					if (a.tparam.in_weak(crvres.apnts[i], rabbit::precision) && b.tparam.in_weak(crvres.bpnts[i], rabbit::precision)) {
						res.ipnts.emplace_back(crvres.apnts[i], crvres.bpnts[i], crvres.pnts[i]);
					}
				}

				res.ipnts.shrink_to_fit();
			}

			return res;
		} else {
			PANIC_TRACED();
		}
	}

	bool __is_really_intersected(
		const malgo2::vector2<double>& avin,
		const malgo2::vector2<double>& bvin,
		const malgo2::vector2<double>& avout,
		const malgo2::vector2<double>& bvout
	) {
		auto m1 = avin.crossmul(bvin);
		auto m2 = avout.crossmul(bvout);
		return (m1 < 0 && m2 > 0) || (m1 > 0 && m2 < 0);
	}

	bool is_really_intersected(const trim2& ain, const trim2& bin, const trim2& aout, const trim2& bout) {
		auto vaout = aout.d1(aout.start());
		auto vain = ain.d1(ain.finish());
		auto vbout = bout.d1(bout.start());
		auto vbin = bin.d1(bin.finish());
		return __is_really_intersected(vain, vaout, vbin, vbout);
	}

	bool is_really_intersected(const trim2& a, double param, const trim2& bin, const trim2& bout) {
		auto vaio = a.d1(param);
		auto vbout = bout.d1(bout.start());
		auto vbin = bin.d1(bin.finish());
		return __is_really_intersected(vaio, vaio, vbin, vbout);
	}

	loop_loop_intersection_result loop_loop_intersection(const loop2& a, const loop2& b) {
		loop_loop_intersection_result ret;

		double aparam = 0;
		double bparam = 0;

		for(int ai = 0; ai < a.edges.size(); ++i) {
			for(int bi = 0; bi < b.edges.size(); ++i) {
				const auto& at = a.edges[ai];
				const auto& bt = b.edges[bi];

				auto ttres = trim_trim_intersection(at, bt);
				gxx::println(ai, bi, ttres);

				for (int i = 0; i < ttres.ipnts.size(); ++i) {
					ipoint ip = ttres.ipnts[i];

					bool afinish = gxx::math::is_same(at.tparam.finish(), ip.a, rabbit::precision);
					bool bfinish = gxx::math::is_same(at.tparam.finish(), ip.a, rabbit::precision);

					if (afinish || bfinish) {
						if (afinish && bfinish) {
							if (is_really_intersected(at, a.edges[ai+1]), bt, b.edges[bi+1]) {
								ret.ipnts.emplace_back(ttres.ipnts[i].a + aparam, ttres.ipnts[i].b + bparam, ttres.ipnts[i].r);
							}
						} else if (afinish) {
							if (is_really_intersected(bt, ip.b, at, a.edges[ai+1])) {
								ret.ipnts.emplace_back(ttres.ipnts[i].a + aparam, ttres.ipnts[i].b + bparam, ttres.ipnts[i].r);
							}
						} else {
							if (is_really_intersected(at, ip.a, bt, b.edges[bi+1])) {
								ret.ipnts.emplace_back(ttres.ipnts[i].a + aparam, ttres.ipnts[i].b + bparam, ttres.ipnts[i].r);
							}
						}
					} else {
						ret.ipnts.emplace_back(ttres.ipnts[i].a + aparam, ttres.ipnts[i].b + bparam, ttres.ipnts[i].r);
					}
				}				
				
				bi++;
				bparam += bt.tparam.maximum - bt.tparam.minimum;  
			};
			gxx::println();

			bi = 0;
			bparam = 0;
			ai++;
			aparam += at.tparam.maximum - at.tparam.minimum;  
		};

		/*std::sort(ret.apnts.begin(), ret.apnts.end());
		std::sort(ret.bpnts.begin(), ret.bpnts.end());

		auto ait = std::unique(ret.apnts.begin(), ret.apnts.end(), [](double ad, double bd) { return gxx::math::is_same(ad,bd,rabbit::precision); });
	    auto bit = std::unique(ret.bpnts.begin(), ret.bpnts.end(), [](double ad, double bd) { return gxx::math::is_same(ad,bd,rabbit::precision); });

	    ret.apnts.erase(ait, ret.apnts.end()); 
		ret.bpnts.erase(bit, ret.bpnts.end()); 

	    if (ret.apnts.size() > 1 && a.edges[a.edges.size()-1].finish().is_same(a.edges[0].start(), rabbit::precision)) ret.apnts.pop_back();
	    if (ret.bpnts.size() > 1 && b.edges[b.edges.size()-1].finish().is_same(b.edges[0].start(), rabbit::precision)) ret.bpnts.pop_back();
*/

		return ret;
	}
}