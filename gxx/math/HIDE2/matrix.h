#ifndef GXX_MATH_MATRIX_H
#define GXX_MATH_MATRIX_H

#include <gxx/array.h>
#include <gxx/math/major.h>
#include <gxx/util/setget.h>
#include <gxx/util/random.h>

#include <gxx/math/vector.h>

namespace gxx {
	namespace math {

		template <typename T, typename Alloc = std::allocator<T>>
		class matrix {
		public:
			size_t sz1;
			size_t sz2;
			T* dat;

			Alloc alloc;
	
			CONSTREF_GETTER(size1, sz1);
			CONSTREF_GETTER(size2, sz2);
	
			matrix(size_t arg1, size_t arg2) : sz1(arg1), sz2(arg2), dat(alloc.allocate(sz1*sz2)) {}
			
			vector<T> row(size_t i) {
				vector<T> ret;
				std::copy(iterator2(dat + sz2 * i), iterator2(dat + sz2 * (i + 1)), ret.begin());
				return ret;
			}

			vector<T> column(size_t i) {
				vector<T> ret;
				std::copy(iterator1(dat + sz1 * i), iterator1(dat + sz1 * (i + 1)), ret.begin());
				return ret;
			}


			//matrix(matrix&& mat) : storage(std::move(mat.storage)), m_size1(mat.m_size1), m_size2(m_size2) {}
			//matrix(const matrix& mat) = delete;
	
			//using iterator1 = matrix_iterator1<matrix>;
			//using iterator2 = matrix_iterator2<matrix>;
	
			//iterator1 begin1() {
			//	return iterator1(*this, 0, 0);
			//}
	//
			//iterator2 begin2() {
			//	return iterator2(*this, 0, 0);
			//}
	//
			//const iterator1 end1() {
			//	return iterator1(*this, m_size1, 0);
			//}
	//
			//const iterator2 end2() {
			//	return iterator2(*this, 0, m_size2);
			//}


	
			/*T& operator()(size_t pos1, size_t pos2) {
				return major_accessor<S,O>::ref(storage, pos1, pos2, m_size1, m_size2);
			}
	
			const T& operator()(size_t pos1, size_t pos2) const {
				return major_accessor<S,O>::const_ref(storage, pos1, pos2, m_size1, m_size2);
			}
	
			static matrix random(size_t size1, size_t size2, const T& minval, const T& maxval) {
				matrix ret(size1, size2);
	
				for (auto& ref : ret.storage) {
					ref = gxx::random_minmax<T>(minval, maxval);
				}
	
				return ret;	
			}*/
		};
	}
}

#endif