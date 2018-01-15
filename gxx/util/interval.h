#ifndef GXX_UTIL_INTERVAL_H
#define GXX_UTIL_INTERVAL_H

#include <gxx/print.h>

namespace gxx {
	template<typename T>
	class interval {
		T minimum;
		T maximum;

	public:
		interval(double minimum, double maximum) : minimum(minimum), maximum(maximum) {
			assert(minimum < maximum);
		}

		//bool include(T val) const {
		//	return val > minimum && val < maximum;
		//}

		bool include(T val, T prec) const {
			return val - minimum > -prec && maximum - val > -prec ;
		}

		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint_to(o, "({},{})", minimum, maximum);
		}
	};
}

#endif