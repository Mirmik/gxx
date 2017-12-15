#ifndef GXX_GEOM_NCURVE_H
#define GXX_GEOM_NCURVE_H

#include <stdlib.h>

#include <gxx/math/matrix.h>
#include <gxx/object_buffer.h>

#include <algorithm>

namespace gxx {
	namespace ngeom {
		constexpr static float infinity = std::numeric_limits<float>::infinity();
		constexpr static float E = 0.00000001;

		using matrix = gxx::math::matrix<float>;
		using vector = gxx::math::vector<float>;

		class point {
		public:
			gxx::math::vector<float> raw;
			point(size_t sz) : raw(sz) {}

			float& operator[](int i) {
				return raw[i];
			}
		};

		class curve {
		public:
			float beg_param;
			float end_param;
			curve(float start, float stop) : beg_param(start), end_param(stop) {};
		};


		class line;

		class infinity_line : public curve {
		public:
			unbounded_array<float> storage;
			size_t n;

			math::vector_unbounded<float> location() { return make_objbuf(storage.begin(), n); }
			math::vector_unbounded<float> direction() { return make_objbuf(storage.begin() + n, n); }
			
			infinity_line(const std::initializer_list<float>& loc, const std::initializer_list<float>& dir) 
				: storage(2*loc.size()), curve(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()), n(loc.size()) {
				assert(loc.size() == dir.size());
				float* ptr = storage.begin();
				for (auto& f : loc) { *ptr++ = f; }
				for (auto& f : dir) { *ptr++ = f; }
			}

			vector evaluate_point(int n, float c) {
				float spd = direction()[n];
				assert(std::fabs(spd) > E);

				float refcoord = location()[n];
				float swift = c - refcoord;
				
				vector vec(location() + direction().scale(swift));
				return vec;
			}
				
			infinity_line(const line& l);
		};

		class line : curve {
		public:
			unbounded_array<float> storage;
			size_t n;

			//line() : curve(0,1) {}
			size_t dim() const { return n; }
			math::vector_unbounded<float> first() { return make_objbuf(storage.begin(), n); }
			math::vector_unbounded<float> second() { return make_objbuf(storage.begin() + n, n); }
			math::vector_unbounded<const float> first() const { return make_objbuf(storage.begin(), n); }
			math::vector_unbounded<const float> second() const { return make_objbuf(storage.begin() + n, n); }
			
			line(const std::initializer_list<float>& a, const std::initializer_list<float>& b) : storage(2*a.size()), curve(0, 1), n(a.size()) {
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

			size_t printTo(gxx::io::ostream& o) const {
				gxx::fprint("ls({}, {})", gxx::object_buffer<float>(storage.begin(), n), gxx::object_buffer<float>(storage.begin()+n, n));
			}
		};

		class multiline : curve {
		public:
			gxx::math::matrix<float> raw;

		public:
			//multiline(){}
			multiline(size_t n, size_t m) : raw(n,m), curve(0,m) {}
			multiline(matrix&& mat) : raw(std::move(mat)), curve(0, raw.size1()) {}
			multiline(const multiline&) = delete;
			multiline(multiline&&) = default;
		};
	}
}

#endif