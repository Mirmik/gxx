#ifndef GXX_MATH_VECTOR_H
#define GXX_MATH_VECTOR_H

#include <gxx/print.h>
#include <gxx/array.h>
#include <algorithm>

namespace gxx {
	namespace math {
		template<typename V> class vector_expression : public gxx::array_printable<V> {
			//V& self() { return *this; }

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

			void fill(auto val) {
				V& self = *static_cast<V*>(this);
				for(auto it = self.begin(); it != self.end(); ++it) {
					*it = val;
				}	
			}
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

			vector(size_t n) : storage(n) {}
			vector(const vector& oth) = default;
		};

		template<typename T>
		class vector_unbounded : public vector_expression<vector_unbounded<T>> {
			objbuf<T> buf;

		public:
			vector_unbounded(objbuf<T> buf) : buf(buf) {}

			T& operator[](int i) {
				return buf[i];
			}
			
			const T& operator[](int i) const {
				return buf[i];
			}

		using iterator = T*;
		using const_iterator = const T*;

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