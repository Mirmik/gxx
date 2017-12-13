#ifndef GXX_MATRIX_H
#define GXX_MATRIX_H

#include <stdlib.h>
#include <gxx/print.h>
#include <gxx/object_buffer.h>
#include <gxx/util/random.h>
#include <utility>

#include <gxx/print/array.h>
#include <gxx/math/vector.h>

#include <gxx/math/major.h>
#include <gxx/array.h>

namespace gxx { namespace math {
	template <typename M>
	class matrix_iterator {
		size_t pos1;
		size_t pos2;
		M& mat;

		public:
		matrix_iterator(M& mat, size_t pos1, size_t pos2) : mat(mat), pos1(pos1), pos2(pos2) {}
		typename M::reference operator*() { return mat(pos1, pos2); }
	};

	template <typename M>
	class matrix_iterator1 : public matrix_iterator<M> {
	public:
		matrix_iterator1(M& mat, size_t pos1, size_t pos2) : matrix_iterator<M>(mat, pos1, pos2) {}
	};

	template <typename M>
	class matrix_iterator2 : public matrix_iterator<M> {
	public:
		matrix_iterator2(M& mat, size_t pos1, size_t pos2) : matrix_iterator<M>(mat, pos1, pos2) {}
	};

	template <typename T, typename U> struct vector_accessor; 
	template <typename T> struct vector_accessor<T,row_major> { using rtype = vector_compact_accessor<T>; using ctype = vector_uncompact_accessor<T>; };
	template <typename T> struct vector_accessor<T,column_major> { using ctype = vector_uncompact_accessor<T>; using rtype = vector_compact_accessor<T>; };		

	//ublas compatible ???
	template<typename M>
	class matrix_expression {};

	template<typename T, typename O = row_major, typename S = unbounded_array<T>>
	class matrix : matrix_expression<matrix<T,O,S>> {
	public:
		size_t m_size1;
		size_t m_size2;

		CONSTREF_GETTER(size1, m_size1);
		CONSTREF_GETTER(size2, m_size2);

		S storage;

		using value_type = typename S::allocator_type::value_type;
		using reference = typename S::allocator_type::reference;		

		using matrix_row = typename vector_accessor<T,O>::rtype;
		using matrix_column = typename vector_accessor<T,O>::ctype;

		matrix() = default;
		matrix(size_t arg1, size_t arg2) : m_size1(arg1), m_size2(arg2), storage(arg1 * arg2) {}
		matrix(matrix&& mat) : storage(std::move(mat.storage)), m_size1(mat.m_size1), m_size2(m_size2) {}
		matrix(const matrix& mat) = delete;

		using iterator1 = matrix_iterator1<matrix>;
		using iterator2 = matrix_iterator2<matrix>;

		iterator1 begin1() {
			return iterator1(*this, 0, 0);
		}

		iterator2 begin2() {
			return iterator1(*this, 0, 0);
		}

		const iterator1 end1() {
			return iterator1(*this, m_size1, 0);
		}

		const iterator2 end2() {
			return iterator1(*this, 0, m_size2);
		}

		T& operator()(size_t pos1, size_t pos2) {
			return major_accessor<S,O>::ref(storage, pos1, pos2, m_size1, m_size2);
		}

		const T& operator()(size_t pos1, size_t pos2) const {
			return major_accessor<S,O>::const_ref(storage, pos1, pos2, m_size1, m_size2);
		}


	/*	//n-кол-во столбцов. m-кол-во строк
		size_t n, m, fsize;
		type* data = nullptr;

	public:
		matrix(size_t columns, size_t rows) : n(columns), m(rows), fsize(n*m) {
			data = new type[n*m];
			memset(data, 0, n*m*sizeof(type));
		}

		matrix(matrix&& oth) : n(oth.n), m(oth.m), data(oth.data) {
			oth.data = nullptr;
		} 

		size_t columns() const { return n; }
		size_t rows() const { return m; }

		void fill(type arg) {
			size_t fsize = n * m;
			type* start = data;
			type* finish = data + fsize;

			while(start != data) {
				*start++ = arg;
			}
		}

		matrix add(const matrix& oth) const {
			matrix ret(n,m);
			size_t fsize = n * m;
			
			type * a = data;;
			type * b = oth.data;
			type * c = ret.data;

			type * end = data + fsize;

			while(a != end) {
				*c++ = *a++ + *b++;
			}

			return ret;
		}

		type& operator()(size_t x, size_t y) {
			return data[y*n + x];
		}

		static matrix diagonal(gxx::object_buffer<type> buf) {
			size_t num = buf.size();
			matrix ret(num, num);
			
			type* dat = ret.data;
			int step = num + 1;
			
			for (int i = 0; i < num; ++i) {
				*dat = *dat++;
				dat += step; 
			}

			return ret;
		}


		static matrix diagonal(std::initializer_list<type> lst) {
			size_t num = lst.size();
			matrix ret(num, num);
			
			type* dat = ret.data;
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
			
			type* dat = ret.data;
			int step = num + 1;
			
			for (int i = 0; i < num; ++i) {
				*dat = 1;
				dat += step; 
			}

			return std::move(ret);	
		}
*/
		static matrix random(size_t size1, size_t size2, const T& minval, const T& maxval) {
			matrix ret(size1, size2);

			for (auto& ref : ret.storage) {
				ref = gxx::random_minmax<T>(minval, maxval);
			}

			return ret;	
		}

		size_t printTo(gxx::io::ostream& o) const {
			size_t ret = 0;
			for (int i1 = 0; i1 < m_size1; ++i1) {
				for (int i2 = 0; i2 < m_size2; ++i2) {
					ret += gxx::print(o, operator()(i1,i2)); 
					ret += o.putchar(' ');
				}	
				ret += o.println();
			}
			return ret;
		}
/*
		void self_add_column(size_t i, const vector<type>& vec) {
			assert(m == vec.size());
			auto it = vec.begin();
			for (auto& ref : column_accessor(i)) {
				ref += *it++;
			}
		}

	
		class iterator1 {
			matrix* mat;
		}






		class column_accessor_t : public gxx::array_printable<column_accessor_t> {
		public:
			matrix& mat;
			size_t i;

			column_accessor_t(matrix& mat, size_t i) : mat(mat), i(i) {}

			class iterator {
			public:
				type* data;
				size_t step;

				iterator(type* data, size_t step = 0) : data(data), step(step) {}

				bool operator != (const iterator& oth) {
					return data != oth.data;
				}

				iterator& operator++() {
					data += step;
					return *this;
				} 

				iterator operator++(int) {
					iterator ret = *this;
					data += step;
					return ret;
				} 

				type& operator*() {
					return * data;
				}
			};

			iterator begin() {
				return iterator(mat.data + i, mat.columns());
			}

			iterator end() {
				return iterator(mat.data + i + mat.fsize);
			}

		};

		column_accessor_t column_accessor(size_t i) {
			assert(i < columns());
			return column_accessor_t(*this, i);
		}

		class row_accessor_t : public gxx::array_printable<row_accessor_t> {
		public:
			matrix& mat;
			size_t i;

			size_t size() const { return mat.columns(); }
			float& operator[](size_t c) { return mat(c,i); }
			float val(size_t c) const { return mat(c,i); }

			row_accessor_t(matrix& mat, size_t i) : mat(mat), i(i) {}
			using iterator = float*;
		};

		row_accessor_t row_accessor(size_t i) {
			assert(i < rows());
			return row_accessor_t(*this, i);
		}

		class const_row_accessor_t : public gxx::array_printable<row_accessor_t> {
		public:
			const matrix& mat;
			size_t i;

			size_t size() const { return mat.columns(); }
			const float& operator[](size_t c) { return mat(c,i); }
			float val(size_t c) const { return mat(c,i); }

			const_row_accessor_t(const matrix& mat, size_t i) : mat(mat), i(i) {}
			using iterator = const float*;
		};

		const_row_accessor_t const_row_accessor(size_t i) const {
			assert(i < rows());
			return const_row_accessor_t(*this, i);
		}*/
	};

}}

#endif