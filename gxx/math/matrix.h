#ifndef GXX_MATRIX_H
#define GXX_MATRIX_H

#include <stdlib.h>
#include <gxx/print.h>
#include <gxx/object_buffer.h>
#include <gxx/util/random.h>
#include <utility>

namespace gxx { namespace math {

	class matrix {
		size_t n, m, fsize;
		float* data = nullptr;

	public:
		matrix(size_t n, size_t m) : n(n), m(m), fsize(n*m) {
			data = new float[n*m];
			memset(data, 0, n*m*sizeof(float));
		}

		matrix(matrix&& oth) : n(oth.n), m(oth.m), data(oth.data) {
			oth.data = nullptr;
		} 

		void fill(float arg) {
			size_t fsize = n * m;
			float* start = data;
			float* finish = data + fsize;

			while(start != data) {
				*start++ = arg;
			}
		}

		matrix add(const matrix& oth) const {
			matrix ret(n,m);
			size_t fsize = n * m;
			
			float * a = data;;
			float * b = oth.data;
			float * c = ret.data;

			float * end = data + fsize;

			while(a != end) {
				*c++ = *a++ + *b++;
			}

			return std::move(ret);
		}

		float& operator()(size_t x, size_t y) {
			return data[y*n + x];
		}

		static matrix diagonal(gxx::object_buffer<float> buf) {
			size_t num = buf.size();
			matrix ret(num, num);
			
			float* dat = ret.data;
			int step = num + 1;
			
			for (int i = 0; i < num; ++i) {
				*dat = *dat++;
				dat += step; 
			}

			return std::move(ret);
		}


		static matrix diagonal(std::initializer_list<float> lst) {
			size_t num = lst.size();
			matrix ret(num, num);
			
			float* dat = ret.data;
			int step = num + 1;
			
			auto it = lst.begin();
			for (int i = 0; i < num; ++i) {
				*dat = *it++;
				dat += step; 
			}

			return std::move(ret);
			
		}

		static matrix identity(size_t num) {
			matrix ret(num, num);
			
			float* dat = ret.data;
			int step = num + 1;
			
			for (int i = 0; i < num; ++i) {
				*dat = 1;
				dat += step; 
			}

			return std::move(ret);	
		}

		static matrix random(size_t n, size_t m, float a, float b) {
			matrix ret(n, m);
			
			float* dat = ret.data;
			float* fin = ret.data + ret.fsize;

			for (; dat != fin; ++dat) {
				*dat = float_random(a,b);
			}

			return std::move(ret);	
		}

		size_t printTo(gxx::io::ostream& o) const {
			float* mat = data;
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					o.print(*mat++); 
					o.putchar(' ');
				}	
				o.println();
			}
			return m * n;
		}
	};

}}

#endif