#ifndef GXX_GEOM_NCURVE_H
#define GXX_GEOM_NCURVE_H

#include <stdlib.h>
#include <gxx/math/matrix.h>
#include <gxx/object_buffer.h>

#include <algorithm>

namespace gxx {
	namespace ngeom {
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

		class point_accessor {
		public:
			float* raw;
			point_accessor(float* data) : raw(data) {}

			float& operator[](int i) {
				return raw[i];
			}			

			float val(int i) {
				return raw[i];
			}
		};

		class const_point_accessor {
		public:
			const float* raw;
			const_point_accessor(const float* data) : raw(data) {}

			const float& operator[](int i) const {
				return raw[i];
			}			

			float val(int i) const {
				return raw[i];
			}
		};

		class curve {
		public:
			float beg_param;
			float end_param;
			curve(float start, float stop) : beg_param(start), end_param(stop) {};
		};

		class line : curve {
		public:
			unbounded_array<float> storage;
			size_t n;

			//line() : curve(0,1) {}
			size_t dim() const { return n; }
			point_accessor first() { return point_accessor(storage.begin()); }
			point_accessor second() { return point_accessor(storage.begin() + n); }
			const const_point_accessor cfirst() const { return const_point_accessor(storage.cbegin()); }
			const const_point_accessor csecond() const { return const_point_accessor(storage.cbegin() + n); }

			line(const std::initializer_list<float>& a, const std::initializer_list<float>& b) : storage(2*a.size()), curve(0, 1), n(a.size()) {
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

			size_t printTo(gxx::io::ostream& o) const {
				gxx::fprint("ls({}, {})", gxx::object_buffer<float>(storage.cbegin(), n), gxx::object_buffer<float>(storage.cbegin()+n, n));
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

		multiline correction_for_one_axis(
			const line& l, 
			int c,
			const vector& corcoords,
			const std::vector<uint8_t>& coords,
			const matrix& cormatrix
		) {
			gxx::println("HelloWorld");
			assert(corcoords.size() == cormatrix.size1());
			assert(coords.size() == cormatrix.size2());
			assert(corcoords.is_sorted());

			float cstart = l.cfirst().val(c);
			float cstop = l.csecond().val(c);
			bool reversed = cstart > cstop;

			float low = reversed ? cstop : cstart;
			float high = reversed ? cstart : cstop;

			dprln("low", low);
			dprln("high", high);
			dprln("reversed", reversed);
			gxx::println(corcoords);

			auto lower = std::lower_bound(corcoords.begin(), corcoords.end(), low);
			auto upper = std::upper_bound(corcoords.begin(), corcoords.end(), high);
			auto distance = std::distance(lower, upper);

			dprln("lower", *lower);
			dprln("upper", *upper);
			dprln("distance", distance);

			multiline ml(l.dim(), distance + 2);
			matrix& mat = ml.raw;

			//auto it = ml.raw.begin1();*/

			//auto fr = cormatrix.const_row_accessor(2);
			//gxx::print(fr);
			return ml;
		}
	}
}

#endif