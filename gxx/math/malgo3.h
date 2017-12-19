#ifndef GXX_MATH_MALGO3_H
#define GXX_MATH_MALGO3_H

#include <gxx/math/util.h>
#include <gxx/print.h>

namespace malgo3 {
	template <typename T>
	struct xyz {
		T x, y, z;
		xyz()=default;
		xyz(T x, T y, T z) : x(x), y(y), z(z) {}
		xyz(const xyz& oth) : x(oth.x), y(oth.y), z(oth.z) {}

		xyz& operator=(const xyz& oth) {
			x = oth.x; y = oth.y; z = oth.z;
			return *this;
		}

		void self_scale(double m) {
			x *= m; y *= m; z *= m;
		}

		xyz scale(double m) {
			return xyz(x*m, y*m, z*m);
		}

		void self_rscale(double m) {
			x /= m; y /= m; z /= m;
		}

		xyz rscale(double m) {
			return xyz(x/m, y/m, z/m);
		}

		double abssqr() {
			return x*x + y*y + z*z;
		}

		double abs() {
			return sqrt(abssqr());
		}	

		void self_normalize() {
			double mod = abs();
			return self_rscale(mod);
		}

		xyz add(const xyz& b) {
			return xyz(x + b.x, y + b.y, z + b.z);
		}		

		xyz sub(const xyz& b) {
			return xyz(x - b.x, y - b.y, z - b.z);
		}		

		xyz vecmul(const xyz& b) {
			return xyz(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
		}

		size_t printTo(gxx::io::ostream& o) const {	return gxx::fprint(o, "({},{},{})", x, y, z); }

		template<typename R>
		void reflect(R& r) {
			r & x;
			r & y;
			r & z;
		}
	};

	template <typename T>
	using vector3 = xyz<T>;

	template <typename T>
	class matrix3 {
	public:
		T a11, a12, a13, a21, a22, a23, a31, a32, a33;

		matrix3() = default;
		matrix3(T a11, T a12, T a13, T a21, T a22, T a23, T a31, T a32, T a33) :
			a11(a11), a12(a12), a13(a13), a21(a21), a22(a22), a23(a23), a31(a31), a32(a32), a33(a33) {}

		matrix3 inverse() const {
			return matrix3(a11, a21, a31, a12, a22, a32, a13, a23, a33);
		}

		auto det() const {
			return a11*(a22*a33-a23*a32) - a12*(a21*a33+a23*a31) + a13*(a21*a32-a22*a31); 
		}

		xyz<T> dot(const xyz<T>& v) const {
			return xyz<T>(
				a11*v.x + a12*v.y + a13*v.z,
				a21*v.x + a22*v.y + a23*v.z,
				a31*v.x + a32*v.y + a33*v.z
			);
		}

		xyz<T> operator*(const xyz<T>& v) const {
			return dot(v);
		}

		matrix3 dot(const matrix3& m) const {
			return matrix3(
				a11*m.a11 + a12*m.a21 + a13*m.a31, a11*m.a12 + a12*m.a22 + a13*m.a32, a11*m.a13 + a12*m.a23 + a13*m.a33,  
				a21*m.a11 + a22*m.a21 + a23*m.a31, a21*m.a12 + a22*m.a22 + a23*m.a32, a21*m.a13 + a22*m.a23 + a23*m.a33,
				a31*m.a11 + a32*m.a21 + a33*m.a31, a31*m.a12 + a32*m.a22 + a33*m.a32, a31*m.a13 + a32*m.a23 + a33*m.a33
			);
		}

		static matrix3 identity() {
			return matrix3(1,0,0,0,1,0,0,0,1);
		}

		static matrix3 zx_rotation(double a, double b) {
			double c1 = cos(a); double s1 = sin(a); double c2 = cos(b); double s2 = sin(b);
			return matrix3(
				c1,			-c2*s1,				s1*s2,
				s1,			c1*c2,				-c1*s2,
				0,			s2,					c2
			);
		}

		static matrix3 zxy_rotation(double a, double b, double c) {
			double c1 = cos(a); double s1 = sin(a); double c2 = cos(b); double s2 = sin(b); double c3 = cos(c); double s3 = sin(c);
			return matrix3(
				c1*c3-s1*s2*s3,			-c2*s1,				c1*s3+c3*s1*s2,
				c3*s1+c1*s2*s3,			c1*c2,				s1*s3-c1*c3*s2,
				-c2*s3,					s2,					c2*c3
			);
		}

		size_t printTo(gxx::io::ostream& o) const {	return gxx::fprint(o, "{} {} {}\r\n{} {} {}\r\n{} {} {}", a11, a12, a13, a21, a22, a23, a31, a32, a33); }
	};

	template <typename T>
	class transform {
		matrix3<T> rotate;
		xyz<T> translate;
		T scl;

		transform() = default;
		transform(const matrix3<T>& mat, const xyz<T>& vec, T scl) : rotate(mat), translate(vec), scl(scl) {}

		xyz<T> doit(const xyz<T>& a) {
			return rotate.dot(a).add(translate);
		}
	};

}

#endif