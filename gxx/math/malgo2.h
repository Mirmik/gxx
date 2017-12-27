#ifndef MALGO2_H
#define MALGO2_H

#include <gxx/print.h>

namespace malgo2 {
	template <typename T>
	class vector2 {
	public:
		union {
			T arr[2];
			struct {
				T x;
				T y;
			};
		};

		vector2()=default;
		vector2(T x, T y) : x(x), y(y) {}
		vector2(const vector2& oth) : x(oth.x), y(oth.y) {}

		vector2& operator=(const vector2& oth) {
			x = oth.x; y = oth.y;
			return *this;
		}

		void self_scale(double m) {
			x *= m; y *= m;
		}

		vector2 scale(double m) const {
			return vector2(x*m, y*m);
		}

		void self_rscale(double m) {
			x /= m; y /= m;
		}

		vector2 rscale(double m) const {
			return vector2(x/m, y/m);
		}

		double abssqr() const {
			return x*x + y*y;
		}

		double abs() const {
			return sqrt(abssqr());
		}	

		void self_normalize() {
			double mod = abs();
			return self_rscale(mod);
		}

		vector2 add(const vector2& b) const {
			return vector2(x + b.x, y + b.y);
		}		

		vector2 sub(const vector2& b) const {
			return vector2(x - b.x, y - b.y);
		}		

		size_t printTo(gxx::io::ostream& o) const {	return gxx::fprint(o, "({},{})", x, y); }

		template<typename R>
		void reflect(R& r) {
			r & x;
			r & y;
		}
	};
}

#endif