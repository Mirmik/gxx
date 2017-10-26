#ifndef GXX_CONTAINER_H
#define GXX_CONTAINER_H

#include <gxx/debug/dprint.h>
#include <gxx/generator.h>

namespace gxx { 
	namespace gen {
		class range : public gxx::generator<int, range> {
			int start;
			int stop;
		
		public:
			range(int start, int stop) : start(start), stop(stop) {
				if (start == stop) nil();
			}
		
			bool next() {
				return ++start != stop;
			}
		
			int value() {
				return start;
			}
		};
		
		template<typename C, typename F>
		class mapping_t : public gxx::generator<typename C::value_type, mapping_t<C,F>> {
			using type = typename C::value_type;
			typename C::const_iterator it;
			typename C::const_iterator eit;
			F f;

		public:
			using value_type = decltype(f(*it));

			mapping_t(const C& ctr, F&& f) : f(f), it(ctr.begin()), eit(ctr.end()) {}
		
			bool next() {
				dprln("mapping ++");
				return ++it != eit;
			}
		
			decltype(auto) value() {
				return f(*it);
			}
		};
		
		template<typename C, typename F>
		mapping_t<C,F> mapping(const C& ctr, F&& f) {
			return mapping_t<C,F>(ctr, std::forward<F>(f));
		} 

		template<typename C, typename F>
		class filter_t : public gxx::generator<typename C::value_type, filter_t<C,F>> {
			using parent = gxx::generator<typename C::value_type, filter_t<C,F>>;
			using type = typename C::value_type;
			typename C::const_iterator it;
			typename C::const_iterator eit;
			F f;
		
		public:
			filter_t(const C& ctr, F&& f) : f(f), it(ctr.begin()), eit(ctr.end()) { if (!find_next()) parent::nil(); }
		
			bool find_next() {
				while (true) {
					if (it == eit) return false;
					if (f(*it)) return true;
					++it; 
				}
			}

			bool next() {
				++it;
				return find_next();
			}
		
			type value() {
				return *it;
			}
		};
		
		template<typename C, typename F>
		filter_t<C,F> filter(const C& ctr, F&& f) {
			return filter_t<C,F>(ctr, std::forward<F>(f));
		} 
	}
}

#endif // GXX_CONTAINER_H
