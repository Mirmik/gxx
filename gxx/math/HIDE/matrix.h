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

#include <gxx/math/matrix_iterator.h>

namespace gxx { namespace math {
	//template <typename T, typename U> struct vector_accessor; 
	//template <typename T> struct vector_accessor<T,row_major> { using rtype = vector_compact_accessor<T>; using ctype = vector_uncompact_accessor<T>; };
	//template <typename T> struct vector_accessor<T,column_major> { using ctype = vector_uncompact_accessor<T>; using rtype = vector_compact_accessor<T>; };		

	//ublas compatible ???
	template <typename M> class matrix_row;
	template <typename M> class matrix_column;
	template <typename M> class matrix_proxy;
	
	template <typename M> class const_matrix_row;
	template <typename M> class const_matrix_column;
	template <typename M> class const_matrix_proxy;

	template <typename A, typename B> class matrix_sub;
	template <typename A, typename B> class matrix_add;
	template <typename A, typename B> class matrix_coord_mul;
	template <typename A, typename B> class matrix_coord_div;

	template<typename M>
	class matrix_expression {
	public:
		matrix_row<M> row(size_t i) {
			M& self = *static_cast<M*>(this);
			return matrix_row<M>(self, i);	
		}
	
		matrix_column<M> column(size_t i) {
			M& self = *static_cast<M*>(this);
			return matrix_column<M>(self, i);
		}

		matrix_proxy<M> proxy(size_t pos1, size_t pos2, size_t sz1, size_t sz2) {
			M& self = *static_cast<M*>(this);
			return matrix_proxy<M>(self, pos1, pos2, sz1, sz2);	
		}
	
		const const_matrix_row<const M> row(size_t i) const {
			const M& self = *static_cast<const M*>(this);
			return const_matrix_row<const M>(self, i);	
		}
	
		const const_matrix_column<const M> column(size_t i) const {
			const M& self = *static_cast<const M*>(this);
			return const_matrix_column<const M>(self, i);
		}

		size_t printTo(gxx::io::ostream& o) const {
			const M& self = *static_cast<const M*>(this);
			size_t ret = 0;
			for (int i1 = 0; i1 < self.size1(); ++i1) {
				for (int i2 = 0; i2 < self.size2(); ++i2) {
					ret += gxx::print(o, self.operator()(i1,i2)); 
					ret += o.putchar(' ');
				}	
				ret += o.println();
			}
			return ret;
		}

		template<typename OM>
		matrix_sub<M,OM> operator-(const OM& v) const {
			const M& self = *static_cast<const M*>(this);
			assert(self.size1() == v.size1() && self.size2() == v.size2());
			return matrix_sub<M,OM>(self, v);
		}

		template<typename OM>
		matrix_add<M,OM> operator+(const OM& v) const {
			const M& self = *static_cast<const M*>(this);
			assert(self.size1() == v.size1() && self.size2() == v.size2());
			return matrix_add<M,OM>(self, v);
		}

		template<typename OM>
		M& operator+=(const OM& v) {
			M& self = *static_cast<M*>(this);
			assert(self.size1() == v.size1() && self.size2() == v.size2());
			
			for (int i1 = 0; i1 < self.size1(); ++i1) {
				for (int i2 = 0; i2 < self.size2(); ++i2) {
					self(i1, i2) += v(i1, i2);		
				}	
			}

			return self;
		}

		/*template<typename OV>
		matrix_add<V,OV> operator+(const OV& v) const {
			const V& self = *static_cast<const V*>(this);
			return matrix_add<V,OV>(self, v);
		}

		template<typename OV>
		matrix_coord_mul<V,OV> operator*(const OV& v) const {
			const V& self = *static_cast<const V*>(this);
			return matrix_coord_mul<V,OV>(self, v);
		}*/				
	};

	template <typename V, typename OV>
	struct matrix_sub : public matrix_expression<matrix_sub<V,OV>> {
		const V& a;
		const OV& b;
		using iterator1 = matrix_iterator1<matrix_sub<V,OV>>;
		using value_type = decltype(a(0,0) - b(0,0));
		matrix_sub(const V& a, const OV& b) : a(a), b(b) {}
		iterator1 begin1() const { return iterator1(*this, 0, 0); }
		const iterator1 end1() const { return iterator1(*this, a.size1(), 0); }
		size_t size1() const { return a.size1(); }
		size_t size2() const { return a.size2(); }
		const auto operator()(size_t i, size_t j) const { return a(i,j) - b(i,j); }
	};

	template <typename V, typename OV>
	struct matrix_add : public matrix_expression<matrix_add<V,OV>> {
		const V& a;
		const OV& b;
		using iterator1 = matrix_iterator1<matrix_add<V,OV>>;
		using value_type = decltype(a(0,0) + b(0,0));
		matrix_add(const V& a, const OV& b) : a(a), b(b) {}
		iterator1 begin1() const { return iterator1(*this, 0, 0); }
		const iterator1 end1() const { return iterator1(*this, a.size1(), 0); }
		size_t size1() const { return a.size1(); }
		size_t size2() const { return a.size2(); }
		const auto operator()(size_t i, size_t j) const { return a(i,j) + b(i,j); }
	};

	/*template <typename V, typename OV>
	struct matrix_add : public matrix_expression<matrix_add<V,OV>> {
		const V& a;
		const OV& b;
		using value_type = decltype(a(0,0) + b(0,0));
		using iterator  = matrixop_iterator<matrix_add<V,OV>>;
		matrix_add(const V& a, const OV& b) : a(a), b(b) {}
		iterator begin() const { return iterator(*this, 0); }
		iterator end() const { return iterator(*this, a.size()); }
		size_t size() const { return a.size(); }
		const auto operator[](size_t i) const { return a[i] + b[i]; }
	};

	template <typename V, typename Scalar>
	struct matrix_coord_mul : public matrix_expression<matrix_coord_mul<V,Scalar>> {
		const V& a;
		const Scalar& b;
		using value_type = decltype(a(0,0) * b);
		using iterator  = matrixop_iterator<matrix_coord_mul<V,Scalar>>;
		matrix_coord_mul(const V& a, const Scalar& b) : a(a), b(b) {}
		iterator begin() const { return iterator(*this, 0); }
		iterator end() const { return iterator(*this, a.size()); }
		size_t size() const { return a.size(); }
		const auto operator[](size_t i) const { return a[i] * b; }
	};*/

	template<typename T, typename O = row_major, typename S = unbounded_array<T>>
	class matrix : public matrix_expression<matrix<T,O,S>> {
	public:
		size_t m_size1;
		size_t m_size2;

		CONSTREF_GETTER(size1, m_size1);
		CONSTREF_GETTER(size2, m_size2);

		S storage;

		using value_type = typename S::allocator_type::value_type;
		using reference = typename S::allocator_type::reference;		
		using const_reference = typename S::allocator_type::const_reference;		

		//using matrix_row = typename vector_accessor<T,O>::rtype;
		//using matrix_column = typename vector_accessor<T,O>::ctype;

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
			return iterator2(*this, 0, 0);
		}

		const iterator1 end1() {
			return iterator1(*this, m_size1, 0);
		}

		const iterator2 end2() {
			return iterator2(*this, 0, m_size2);
		}

		T& operator()(size_t pos1, size_t pos2) {
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
		}
	};

	template <typename M>
	class matrix_proxy : public matrix_expression<matrix_proxy<M>> {
		M& mat;
		size_t pos1;
		size_t pos2;
		size_t sz1;
		size_t sz2;
	
		using iterator1 = matrix_iterator1<M>;
		using iterator2 = matrix_iterator2<M>;
		using const_iterator1 = matrix_const_iterator1<M>;
		using const_iterator2 = matrix_const_iterator2<M>;
	
	public:
		using value_type = typename M::value_type;
		using reference = typename M::reference;
		using const_reference = typename M::const_reference;
		matrix_proxy(M& mat, size_t pos1, size_t pos2, size_t sz1, size_t sz2) : mat(mat), pos1(pos1), pos2(pos2), sz1(sz1), sz2(sz2) {}

		size_t size1() const { return sz1; }
		size_t size2() const { return sz2; }

		auto& operator()(size_t a, size_t b) {
			return mat(a+pos1,b+pos2);
		} 

		const auto& operator()(size_t a, size_t b) const {
			return mat(a+pos1,b+pos2);
		} 

		iterator1 begin1() {
			return iterator1(*this, pos1, pos2);
		}

		iterator2 begin2() {
			return iterator2(*this, pos1, pos2);
		}

		const iterator1 end1() {
			return iterator1(*this, pos1 + sz1, pos2);
		}

		const iterator2 end2() {
			return iterator2(*this, pos1, pos2 + sz2);
		}

	};

	template<typename M> 
	class matrix_row : public vector_expression<matrix_row<M>> {
		M& mat;
		size_t ridx;

		using iterator = matrix_iterator2<M>;
		using const_iterator = matrix_const_iterator2<M>;

	public:	
		using value_type = typename M::value_type;

		size_t size() const {
			return mat.size2();
		}

		matrix_row(M& mat, size_t i) : mat(mat), ridx(i) {}
		template <typename V>
		matrix_row& operator=( const V& v ) { vector_expression<matrix_row<M>>::copy(v); return *this; }

		typename M::reference operator[](int i) {
			return mat(ridx, i);
		}

		typename M::const_reference operator[](int i) const {
			return mat(ridx, i);
		}

		iterator begin() {
			return iterator(mat, ridx, 0);
		}

		const iterator end() {
			return iterator(mat, ridx, mat.size2());
		}

		const_iterator begin() const {
			return const_iterator(mat, ridx, 0);
		}

		const const_iterator end() const {
			return const_iterator(mat, ridx, mat.size2());
		}
	};

	template<typename M> 
	class matrix_column : public vector_expression<matrix_column<M>> {
		M& mat;
		size_t cidx;

		using iterator = matrix_iterator1<M>;
		using const_iterator = matrix_const_iterator1<M>;

	public:	

		size_t size() const {
			return mat.size1();
		}

		matrix_column(M& mat, size_t i) : mat(mat), cidx(i) {}

		iterator begin() {
			return iterator(mat, 0, cidx);
		}

		const iterator end() {
			return iterator(mat, mat.size1(), cidx);
		}

		const_iterator begin() const {
			return const_iterator(mat, 0, cidx);
		}

		const const_iterator end() const {
			return const_iterator(mat, mat.size1(), cidx);
		}
	};

	template<typename M> 
	class const_matrix_row : public vector_expression<const_matrix_row<M>> {
		M& mat;
		size_t ridx;

		using const_iterator = matrix_const_iterator2<M>;

	public:	
		using value_type = typename M::value_type;

		const_matrix_row(M& mat, size_t i) : mat(mat), ridx(i) {}

		typename M::reference operator[](int i) {
			return mat(ridx, i);
		}

		typename M::const_reference operator[](int i) const {
			return mat(ridx, i);
		}

		size_t size() const {
			return mat.size2();
		}

		const_iterator begin() const {
			return const_iterator(mat, ridx, 0);
		}

		const const_iterator end() const {
			return const_iterator(mat, ridx, mat.size2());
		}
	};

	template<typename M> 
	class const_matrix_column : public vector_expression<const_matrix_column<M>> {
		M& mat;
		size_t cidx;

		using iterator = matrix_iterator1<M>;
		using const_iterator = matrix_const_iterator1<M>;

	public:	
		const_matrix_column(M& mat, size_t i) : mat(mat), cidx(i) {}

		const_iterator begin() const {
			return const_iterator(mat, 0, cidx);
		}

		const const_iterator end() const {
			return const_iterator(mat, mat.size1(), cidx);
		}
	};

	template<typename M>
	matrix_row<M> make_matrix_row(M& mat, size_t i) {
		return matrix_row<M>(mat, i);
	}

	template<typename M>
	matrix_column<M> make_matrix_column(M& mat, size_t i) {
		return matrix_column<M>(mat, i);
	}
}}

#endif