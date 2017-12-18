#ifndef GXX_NGEOM_H
#define GXX_NGEOM_H

#include <gxx/array.h>
#include <gxx/objbuf.h>
#include <gxx/math/malgo.h>

#include <limits>

namespace gxx { 
	namespace ngeom {

		constexpr static float infinity = std::numeric_limits<float>::infinity();
		constexpr static float E = 0.00000001;

		class coordinates {
		public:
			unbounded_array<float> raw;
			coordinates(size_t size) : raw(size) {}
			coordinates(gxx::objbuf<float> buf) : raw(buf) {}	
			coordinates(const std::initializer_list<float>& buf) : raw(buf) {}	
			size_t dim() const { return raw.size(); }
			float& operator[](int i) { return raw[i]; }
			const float& operator[](int i) const { return raw[i]; }

			size_t printTo(gxx::io::ostream& o) const {
				gxx::print(raw);
			}
		};

		class point : public coordinates {
		public:
			point(size_t sz) : coordinates(sz) {}
			point(const objbuf<float>& buf) : coordinates(buf) {}
			point(const std::initializer_list<float>& lst) : coordinates(lst) {}
			point(const point& oth) : coordinates(oth) {}
		};

		class direction : public coordinates {
		public:
			direction(gxx::objbuf<float> buf) : coordinates(buf) {
				malgo::vector_quick_normalize(raw.data(), raw.size(), raw.data());
			}			
		};

		point linear_interpolation_2point(const point& a, const point& b, float k) {
			size_t dim = a.dim();
			float tmp[dim];
			point c(dim);
			
			auto A = a.raw.data();
			auto B = b.raw.data();
			auto C = c.raw.data();

			malgo::vector_scale(A, dim, 1 - k, tmp);
			malgo::vector_scale(B, dim, k, C);
			malgo::vector_add(tmp, C, dim, C);
			return c;
		}

	}
}
#endif