#ifndef GXX_MATH_VECTOR_H
#define GXX_MATH_VECTOR_H

#include <gxx/print.h>
#include <gxx/array.h>
#include <algorithm>

namespace gxx {
	namespace math {
		//template <typename V, typename OV> class vector;
		template <typename V, typename OV> class vector_sub;
		template <typename V, typename OV> class vector_add;
		template <typename V, typename OV> class vector_scale;
		//template <typename V, typename OV> class vector_coord_div;

		template<typename V> class vector_expression : public gxx::array_printable<V> {
		public:
			bool is_sorted() const {
				const V& self = *static_cast<const V*>(this);
				return std::is_sorted(self.begin(), self.end());
			}

			template<typename Array>
			void self_add(const Array& array) {
				V& self = *static_cast<V*>(this);
				auto sit = array.begin();
				for(auto it = self.begin(); it != self.end(); ++it) {
					*it += *sit++;
				}	
			}

			float abs() {
				V& self = *static_cast<V*>(this);
				float sum = 0;
				for (const auto& s : self) {
					sum += s*s;
				}
				return sqrt(sum);
			}

			void self_normalize() {
				V& self = *static_cast<V*>(this);
				float mod = abs();
				for (auto& s : self) {
					s /= mod;
				} 
			}

			void fill(auto val) {
				V& self = *static_cast<V*>(this);
				for(auto it = self.begin(); it != self.end(); ++it) {
					*it = val;
				}	
			}

			//template<typename OV>
			//& operator=(const OV& v) {
				//V& self = *static_cast<V*>(this);
				//std::copy(v.begin(), v.end(), self.begin());
				//return self;
			//}

			template<typename OV>
			void copy(const OV& v) {
				V& self = *static_cast<V*>(this);
				std::copy(v.begin(), v.end(), self.begin());
			}

			template<typename OV>
			vector_sub<V,OV> operator-(const OV& v) const {
				const V& self = *static_cast<const V*>(this);
				return vector_sub<V,OV>(self, v);
			}

			template<typename OV>
			vector_add<V,OV> operator+(const OV& v) const {
				const V& self = *static_cast<const V*>(this);
				return vector_add<V,OV>(self, v);
			}

			template<typename OV>
			vector_scale<V,OV> scale(const OV& v) const {
				const V& self = *static_cast<const V*>(this);
				return vector_scale<V,OV>(self, v);
			}								
		};

		template <typename V>
		struct vectorop_iterator : public std::iterator<std::random_access_iterator_tag, typename V::value_type> {
			const V& vec;
			int n;
			vectorop_iterator(const V& vec, size_t n) : vec(vec), n(n) {}
			vectorop_iterator& operator++() { ++n; return *this; }
			typename std::iterator<std::random_access_iterator_tag, typename V::value_type>::difference_type operator-(const vectorop_iterator& oth) { return n - oth.n; }
			typename std::iterator<std::random_access_iterator_tag, typename V::value_type>::value_type operator*() { return vec[n]; }
		};

		template <typename V, typename OV>
		struct vector_sub : public vector_expression<vector_sub<V,OV>> {
			const V& a;
			const OV& b;
			using value_type = decltype(a[0] - b[0]);
			using iterator  = vectorop_iterator<vector_sub<V,OV>>;
			vector_sub(const V& a, const OV& b) : a(a), b(b) {}
			iterator begin() const { return iterator(*this, 0); }
			iterator end() const { return iterator(*this, a.size()); }
			size_t size() const { return a.size(); }
			const auto operator[](size_t i) const { return a[i] - b[i]; }
		};

		template <typename V, typename OV>
		struct vector_add : public vector_expression<vector_add<V,OV>> {
			const V& a;
			const OV& b;
			using value_type = decltype(a[0] + b[0]);
			using iterator  = vectorop_iterator<vector_add<V,OV>>;
			vector_add(const V& a, const OV& b) : a(a), b(b) {}
			iterator begin() const { return iterator(*this, 0); }
			iterator end() const { return iterator(*this, a.size()); }
			size_t size() const { return a.size(); }
			const auto operator[](size_t i) const { return a[i] + b[i]; }
		};

		template <typename V, typename Scalar>
		struct vector_scale : public vector_expression<vector_scale<V,Scalar>> {
			const V& a;
			const Scalar& b;
			using value_type = decltype(a[0] * b);
			using iterator  = vectorop_iterator<vector_scale<V,Scalar>>;
			vector_scale(const V& a, const Scalar& b) : a(a), b(b) {}
			iterator begin() const { return iterator(*this, 0); }
			iterator end() const { return iterator(*this, a.size()); }
			size_t size() const { return a.size(); }
			const auto operator[](size_t i) const { return a[i] * b; }
		};

		template<typename T, typename S = gxx::unbounded_array<T>>
		class vector : public vector_expression <vector<T,S>> {
			S storage;

		public:
			using value_type =		typename S::value_type;
			using reference = 		typename S::reference;
			using const_reference = typename S::const_reference;
			using iterator = 		typename S::iterator;
			using const_iterator = 	typename S::const_iterator;

			iterator begin() {
				return storage.begin();
			}

			const iterator end() {
				return storage.end();
			}

			const_iterator begin() const {
				return storage.begin();
			}

			const const_iterator end() const {
				return storage.end();
			}

			size_t size() const {
				return storage.size();
			}

			reference operator()(size_t i) {
				return storage[i];
			}

			reference operator[](size_t i) {
				return storage[i];
			}

			const_reference operator[](size_t i) const {
				return storage[i];
			}

			vector(int n) : storage(n) {}
			vector(long unsigned n) : storage(n) {}
			//vector(const vector& oth) = default;

			template<typename Array>
			vector(Array&& oth) : storage(oth.size()) {
				vector_expression<vector<T,S>>::copy(oth);
			}

			vector(const std::initializer_list<T> oth) : storage(oth.size()) {
				vector_expression<vector<T,S>>::copy(oth);
			}
		};

		template<typename T>
		class vector_unbounded : public vector_expression<vector_unbounded<T>> {
			objbuf<T> buf;

		public:
			//template <typename U>
			//using vector_expression<vector_unbounded<T>>::operator=;

			template<typename V>
			vector_unbounded& operator=( const V& v ) { vector_expression<vector_unbounded<T>>::copy(v); return *this; }

			vector_unbounded(objbuf<T> buf) : buf(buf) {}

			T& operator[](int i) {
				return buf[i];
			}
			
			const T& operator[](int i) const {
				return buf[i];
			}

		using iterator = T*;
		using const_iterator = const T*;

			size_t size() const {
				return buf.size();
			}

			iterator begin() {
				return buf.begin();
			}

			const iterator end() {
				return buf.end();
			}

			const_iterator begin() const {
				return buf.begin();
			}

			const const_iterator end() const {
				return buf.end();
			}

		};
	}
}

#endif