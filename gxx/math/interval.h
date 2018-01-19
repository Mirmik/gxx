#ifndef GXX_MATH_INTERVAL_H
#define GXX_MATH_INTERVAL_H

#include <vector>
#include <algorithm>

#include <gxx/print.h>
#include <gxx/print/stdprint.h>
#include <gxx/math/util.h>

namespace gxx {
	namespace math {
		template<typename T> struct interval_union;

		template<typename T>
		struct interval {
			T minimum;
			T maximum;

			interval(){}
			interval(T minimum, T maximum) : minimum(minimum), maximum(maximum) {}

			bool in(T pnct) {
				return minimum < pnct && pnct < maximum;
			}

			operator bool() const {
				return minimum <= maximum;
			}

			bool is_degenerate() {
				minimum == maximum;
			}

			bool operator < (const interval& oth) const {
				return minimum < oth.minimum || maximum < oth.maximum;
			}

			void divide(T pnct) {
				interval_union<T> ret;
				if (in(pnct)) {
					ret.vec.push_back(interval(minimum, pnct));
					ret.vec.push_back(interval(minimum, pnct));
				} else {
					ret.vec.push_back(*this);
				};
				return ret;
			}

			interval simple_intersect(interval oth) const {
				return interval(gxx::math::maximum<T>(minimum, oth.minimum), gxx::math::minimum<T>(maximum, oth.maximum));
			}

			bool is_intersected_with(const interval& oth) const {
				if (maximum < oth.minimum || minimum > oth.maximum) return false;
				return true; 
			}

			interval_union<T> intersect(interval oth) const {
				return interval_union<T> { simple_intersect(oth) };
			}

			interval_union<T> difference(interval oth) const {
				interval_union<T> ret;
				interval intersection = simple_intersect(oth);

				if (intersection) {
					if (minimum != intersection.minimum) {
						ret.vec.push_back(interval(minimum, intersection.minimum));	
					}

					if (maximum != intersection.maximum) {
						ret.vec.push_back(interval(intersection.maximum, maximum));		
					}
				}
				return ret;
			}

			interval simple_combine(interval oth) const {
				return interval(gxx::math::minimum<T>(minimum, oth.minimum), gxx::math::maximum<T>(maximum, oth.maximum));
			}

			interval_union<T> combine(interval oth) const {
				interval_union<T> ret;
				interval intersection = simple_intersect(oth);

				if (intersection) {
					ret.vec.push_back(simple_combine(oth));	
				}

				else {
					ret.vec.push_back(*this);
					ret.vec.push_back(oth);
				}
				return ret;
			}

			size_t printTo(gxx::io::ostream& o) const {
				return gxx::fprint_to(o, "({},{})", minimum, maximum);
			}			
		};

		template<typename T>
		struct interval_union {
			struct intersected_group {
				using begtype = typename std::vector<interval<T>>::const_iterator;
				using endtype = typename std::vector<interval<T>>::const_iterator;

				begtype begin_ait;
				endtype end_ait;
				begtype begin_bit;
				endtype end_bit;

				intersected_group(auto a, auto ea, auto b, auto eb) : begin_ait(a), end_ait(ea), begin_bit(b), end_bit(eb) {}

				operator bool() {
					return begin_ait != end_ait && begin_bit != end_bit;
				} 

				//Для weak intersection
				interval<T> combine() {
					if (begin_ait == end_ait) return *begin_bit;
					if (begin_bit == end_bit) return *begin_ait;
					
					T minimum = begin_ait->minimum;
					T maximum = begin_ait->maximum;

					for (auto it = begin_ait; it != end_ait; ++it) { 
						if (it->minimum < minimum) minimum = it->minimum;
						if (it->maximum > maximum) maximum = it->maximum;
					}

					for (auto it = begin_bit; it != end_bit; ++it) { 
						if (it->minimum < minimum) minimum = it->minimum;
						if (it->maximum > maximum) maximum = it->maximum;
					}

					return interval<T>(minimum, maximum);
				}

				//Для full intersection
				interval_union intersect() {
					interval_union ret;
					if (begin_ait == end_ait) return ret;
					if (begin_bit == end_bit) return ret;

					auto ait = begin_ait;
					auto bit = begin_bit;

					while(1) {
						auto r = ait->simple_intersect(*bit);
						if (r) ret.vec.push_back(r);
						auto amax = ait->maximum;
						auto bmax = bit->maximum;
						if (amax < bmax) {
							if (++ait == end_ait) return ret;
						} else {
							if (++bit == end_bit) return ret;							
						}
					}
				}
			};

			std::vector<interval<T>> vec;

			interval_union(const std::initializer_list<interval<T>> lst) {
				for (const auto& i : lst) {
					if (i) vec.emplace_back(i);
				} 
				std::sort(vec.begin(), vec.end());
			}

			interval_union() = default;

			static intersected_group __find_intersected_group(auto ait, auto end_ait, auto bit, auto end_bit) {
				auto a = ait;
				auto b = bit;
				auto anext = ait;
				auto bnext = bit;
				++anext;
				++bnext;

				while(1) {
					if (anext != end_ait) if ((anext)->is_intersected_with(*b)) { ++a; ++anext; continue; }
					if (bnext != end_bit) if ((bnext)->is_intersected_with(*a)) { ++b; ++bnext; continue; }
					return intersected_group(ait, anext, bit, bnext);
				}
			}

			static intersected_group find_intersected_group_weak(auto ait, auto end_ait, auto bit, auto end_bit) {
				if (ait == end_ait) {
					auto ebit = bit;
					return intersected_group(ait, ait, bit, ++ebit);
				}

				if (bit == end_bit) {
					auto eait = ait;
					return intersected_group(ait, ++eait, bit, bit);
				}

				if ( ! ait->is_intersected_with(*bit) ) {
					if (*ait < *bit) {
						auto eait = ait;
						return intersected_group(ait, ++eait, bit, bit);
					} 
					else {
						auto ebit = bit;
						return intersected_group(ait, ait, bit, ++ebit);
					} 
				}

				return __find_intersected_group(ait, end_ait, bit, end_bit);
			};

			static intersected_group find_intersected_group(auto ait, auto eait, auto bit, auto ebit) {
				while(1) {
					if (ait == eait || bit == ebit) return intersected_group(eait, eait, ebit, ebit);
					if ( ! ait->is_intersected_with(*bit) ) {
						if (*ait < *bit) ++ait; else ++bit;
					} else break;
				}

				return __find_intersected_group(ait, eait, bit, ebit);
			};

			interval_union combine(const interval_union& oth) const {
				interval_union ret;

				auto ait = vec.begin();
				auto eait = vec.end();
				auto bit = oth.vec.begin();
				auto ebit = oth.vec.end();
				for(; ait != eait || bit != ebit;) {
					auto group = gxx::math::interval_union<double>::find_intersected_group_weak(ait, eait, bit, ebit);
					ret.vec.push_back(group.combine());
					ait = group.end_ait;
					bit = group.end_bit;
				}					
				return ret;
			}

			interval_union intersect(const interval_union& oth) const {
				interval_union ret;

				auto ait = vec.begin();
				auto eait = vec.end();
				auto bit = oth.vec.begin();
				auto ebit = oth.vec.end();
				for(; ait != eait || bit != ebit;) {
					auto group = gxx::math::interval_union<double>::find_intersected_group(ait, eait, bit, ebit);
					if (!group) return ret;
					auto r = group.intersect();
					std::copy(r.vec.begin(), r.vec.end(), std::back_inserter(ret.vec));
					ait = group.end_ait;
					bit = group.end_bit;
				}					
				return ret;
			}
 
			size_t printTo(gxx::io::ostream& o) const {
				return gxx::print_to(o, vec);
			}
		};
	}
}

#endif