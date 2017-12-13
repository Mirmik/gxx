#ifndef GXX_MATH_VECTOR_H
#define GXX_MATH_VECTOR_H

#include <gxx/print.h>

namespace gxx {
	namespace math {
		template<typename T>
		class vector_uncompact_accessor {

		};

		template<typename T>
		class vector_compact_accessor {

		};

		template<typename type>
		class vector {
			size_t n;
			type* data = nullptr;

		public:
			type* begin() const {
				return data;
			}

			type* end() const {
				return data+n;
			}

			size_t size() const {
				return n;
			}

			type& operator()(size_t i) {
				return *(data + i);
			}

			vector(size_t n) : n(n) {
				data = new type[n];
			}			

			type& operator[](size_t i) {
				return *(data + i);
			} 

			vector add(const vector& oth) const {
				assert(n == oth.n);
				vector ret(n);

				type * a = data;;
				type * b = oth.data;
				type * c = ret.data;

				type * end = data + n;

				while(a != end) {
					*c++ = *a++ + *b++;
				}
			}

			bool is_sorted() const {
				auto it = begin();
				auto eit = end();
				float cur = *it++;

				for (; it != eit; ++it) {
					if (cur > *it) return false;
					cur = *it;
				}

				return true;
			}

			size_t printTo(gxx::io::ostream& o) const {
				for(int i = 0; i < n; ++i) {
					o.print(*(data + i));
					if (i != n-1) o.putchar(' ');
				}
			}
		};
	}
}

#endif