#ifndef MALGO2_H
#define MALGO2_H

#include <gxx/math/util.h>
#include <gxx/print.h>
#include <cmath>

namespace malgo2 {
	static constexpr double standart_precision = 0.00000001;

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


		bool is_same(const vector2& oth, double prec = malgo2::standart_precision) {
			return sub(oth).abs0() < prec;
		}

		bool is_not_same(const vector2& oth, double prec = malgo2::standart_precision) {
			return !is_same(oth,prec);
		}

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

		T abs0() {
			return std::max(std::fabs(x), std::fabs(y));
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

		void self_sub(const vector2& b) {
			x -= b.x; y -= b.y;
		}		

		void self_reverse() {
			x = -x; y = -y;
		}

		vector2 reverse() const {
			return vector2(-x,-y);
		}

		inline vector2 operator-() const {
			return reverse();
		}		

		inline vector2 operator-(const vector2& b) const {
			return sub(b);
		}		

		double sclmul(const vector2& b) const {
			return x * b.x + y * b.y; 
		}

		double crossmul(const vector2& b) const {
			return x * b.y - b.x * y; 
		}

		double evalrot(const vector2& b) {
			auto c = sclmul(b);
			auto s = crossmul(b);
			return atan2(s,c);
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