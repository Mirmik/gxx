#ifndef GXX_GEOM_NCURVE_H
#define GXX_GEOM_NCURVE_H

//#include <gxx/objbuf.h>
#include <gxx/geom/ngeom.h>
#include <gxx/exception.h>

namespace gxx {
	namespace ngeom {
		class curve {
		public:
			virtual point d0(float t) = 0;
		};

		class bounded_curve : public curve {
		public:
			float tmin;
			float tmax;
			bounded_curve(float tmin, float tmax) : tmin(tmin), tmax(tmax) {};
		};

		class line;

		class line : public curve {
		public:
			point l;
			direction d;

			CONSTREF_GETTER(loc, l);
			CONSTREF_GETTER(dir, d);
			
			/*infinity_line(const std::initializer_list<float>& loc, const std::initializer_list<float>& dir) 
				: storage(2*loc.size()), curve(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()), n(loc.size()) {
				assert(loc.size() == dir.size());
				float* ptr = storage.begin();
				for (auto& f : loc) { *ptr++ = f; }
				for (auto& f : dir) { *ptr++ = f; }
			}

			vector evaluate_point(int n, float c) {
				//float spd = direction()[n];
				//assert(std::fabs(spd) > E);
//
				//float refcoord = location()[n];
				//float swift = c - refcoord;
				//
				//vector vec(location() + direction().scale(swift));
				//return vec;
			}
				
			infinity_line(const line& l);*/
		};

		class line_segment : public bounded_curve {
		public:
			point a;
			point b;

			line_segment(point a, point b) : a(a), b(b), bounded_curve(0,1) {}
			//line_segment(std::initializer_list<float> a, gxx::objbuf<float> b) : a(a), b(b), bounded_curve(0,1) {}

			size_t dim() const { return a.dim(); }
			
			point& pnt1() { return a; }
			point& pnt2() { return b; }
			const point& pnt1() const { return a; }
			const point& pnt2() const { return b; }

			point d0(float t) { 
				return ngeom::linear_interpolation_2point(pnt1(), pnt2(), t);
			};
			
			/*line(const std::initializer_list<float>& a, const std::initializer_list<float>& b) : storage(2*a.size()), curve(0, 1), n(a.size()) {
				assert(a.size() == b.size());
				float* ptr = storage.begin();
				for (auto& f : a) { *ptr++ = f; }
				for (auto& f : b) { *ptr++ = f; }
			}

			template <typename A, typename B>
			line(const A& a, const B& b) : storage(2*a.size()), curve(0, 1), n(a.size()) {
				assert(a.size() == b.size());
				float* ptr = storage.begin();
				for (auto& f : a) { *ptr++ = f; }
				for (auto& f : b) { *ptr++ = f; }
			}

			line(line&&) = delete;
			line(const line&) = delete;

			float length() {
				float sum = 0, a, b;
				for (int i = 0; i < n; ++i) {
					a = storage[i];
					b = storage[i+n];
					sum += (b - a) * (b - a); 
				}
				return sqrt(sum);
			}

			infinity_line to_infinity_line() const {
				return infinity_line(*this);
			}
*/
			size_t printTo(gxx::io::ostream& o) const {
				gxx::fprint("ls({}, {})", a, b);
			}
		};

		class multiline : public bounded_curve {
		public:
			//gxx::math::matrix<float> raw;

		public:
			//multiline(size_t n, size_t m) : raw(n,m), bounded_curve(0,m) {}
			//multiline(matrix&& mat) : raw(std::move(mat)), bounded_curve(0, raw.size1()) {}
			//multiline(const multiline&) = delete;
			//multiline(multiline&&) = default;

			point d0(float t);
		};
	}
}

#endif