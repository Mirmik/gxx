#ifndef GXX_MATH_VECTOR_H
#define GXX_MATH_VECTOR_H

#include <gxx/util/setget.h>
#include <gxx/util/random.h>
#include <gxx/object_buffer.h>

#include <memory>

namespace gxx {
	namespace math {
		template <typename T, typename Alloc = std::allocator<T>>
		class vector {
		public:	
			size_t sz;
			T* dat;

			Alloc alloc;

			CONSTREF_GETTER(size, sz);
	
			//using value_type = typename S::allocator_type::value_type;
			//using reference = typename S::allocator_type::reference;		
			//using const_reference = typename S::allocator_type::const_reference;		
	
			//using vector_row = typename vector_accessor<T,O>::rtype;
			//using vector_column = typename vector_accessor<T,O>::ctype;
	
			vector() = default;
			
			vector(size_t arg) : sz(arg) {
				dat = alloc.allocate(arg);
			}

			vector(const gxx::objbuf<float> arg) : vector(arg.size()) {
				std::copy(arg.begin(), arg.end(), dat);
			}

			~vector() {
				alloc.deallocate(dat);
			}

			//vector(vector&& mat) : storage(std::move(mat.storage)), m_size1(mat.m_size1), m_size2(m_size2) {}
			//vector(const vector& vec) = delete;
	
			//using iterator1 = vector_iterator1<vector>;
			//using iterator2 = vector_iterator2<vector>;
	
			using iterator = T*;
			using const_iterator = const T*;

			iterator begin() {
				return dat;
			}

			const iterator end() {
				return dat + sz;
			}
	
			const_iterator begin() const {
				return dat;
			}

			const const_iterator end() const {
				return dat + sz;
			}
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
	
			T& operator()(size_t pos) {
				return dat + pos;
			}
	
			const T& operator()(size_t pos) const {
				return dat + pos;
			}

			T& operator[](size_t pos) {
				return dat + pos;
			}
	
			const T& operator[](size_t pos) const {
				return dat + pos;
			}
	
			static vector random(size_t size, const T& minval, const T& maxval) {
				vector ret(size);
	
				for (auto ptr = ret.dat; ptr != ret.dat + ret.sz; ++ptr) {
					*ptr = gxx::random_minmax<T>(minval, maxval);
				}
	
				return ret;	
			}

			T abssqr() {
				T sum();
				for (auto it = dat; it != dat + sz; ++it) {
					T v = *it++;
					sum += v*v;
				} 
				return sum;
			}

			T abs() {
				return sqrt(abssqr());
			}

			T quick_invabs() {
				return quick_rsqrt(abssqr());
			}

			void self_normalize() {
				T mod = abs();
				self_rscale(mod);			
			}

			void self_quick_normalize() {
				T invabs = quick_invabs();
				self_scale(invabs);
			}
		};
	}
}

#endif