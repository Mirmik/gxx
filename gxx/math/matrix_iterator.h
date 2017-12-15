#ifndef GXX_MATRIX_ITERATOR_H
#define GXX_MATRIX_ITERATOR_H

namespace gxx { namespace math {
	template <typename M>
	struct matrix_iterator_base : public std::iterator<std::random_access_iterator_tag, typename M::value_type> {};

	template <typename M>
	class matrix_iterator : public matrix_iterator_base<M> {
	protected:
		size_t pos1;
		size_t pos2;
		M& mat;

	public:
		matrix_iterator(M& mat, size_t pos1, size_t pos2) : mat(mat), pos1(pos1), pos2(pos2) {}
		typename M::reference operator*() { return mat(pos1, pos2); }
		bool operator!=(const matrix_iterator& oth) const {
			return pos1 != oth.pos1 || pos2 != oth.pos2;
		}
	};

	template <typename M>
	class matrix_const_iterator : public matrix_iterator_base<M> {
	protected:
		size_t pos1;
		size_t pos2;
		const M& mat;

	public:
		matrix_const_iterator(const M& mat, size_t pos1, size_t pos2) : mat(mat), pos1(pos1), pos2(pos2) {}
		typename M::const_reference operator*() const { return mat(pos1, pos2); }
		bool operator!=(const matrix_const_iterator& oth) const {
			return pos1 != oth.pos1 || pos2 != oth.pos2;
		}
	};

	template <typename M> class matrix_iterator1;
	template <typename M> class matrix_iterator2;

	template <typename M>
	class matrix_iterator1 : public matrix_iterator<M> {
	public:
		matrix_iterator1(M& mat, size_t pos1, size_t pos2) : matrix_iterator<M>(mat, pos1, pos2) {}
		matrix_iterator1& operator++() { ++matrix_iterator<M>::pos1; return *this; }
		typename std::iterator_traits<matrix_iterator1>::difference_type operator-(const matrix_iterator1& oth) { return matrix_iterator<M>::pos1 - oth.pos1; }
		matrix_iterator2<M> begin() { return matrix_iterator2<M>(matrix_iterator<M>::mat,matrix_iterator<M>::pos1,matrix_iterator<M>::pos2); }
		const matrix_iterator2<M> end() { return matrix_iterator2<M>(matrix_iterator<M>::mat,matrix_iterator<M>::pos1,matrix_iterator<M>::mat.size2()); }
	};

	template <typename M>
	class matrix_iterator2 : public matrix_iterator<M> {
	public:
		matrix_iterator2(M& mat, size_t pos1, size_t pos2) : matrix_iterator<M>(mat, pos1, pos2) {}
		matrix_iterator2& operator++() { ++matrix_iterator<M>::pos2; return *this; }
		typename std::iterator_traits<matrix_iterator2>::difference_type operator-(const matrix_iterator2& oth) { return matrix_iterator<M>::pos2 - oth.pos2; }
	};

	template <typename M>
	class matrix_const_iterator1 : public matrix_const_iterator<M> {
	public:
		matrix_const_iterator1(M& mat, size_t pos1, size_t pos2) : matrix_const_iterator<M>(mat, pos1, pos2) {}
		matrix_const_iterator1& operator++() { ++matrix_const_iterator<M>::pos1; return *this; }
		typename std::iterator_traits<matrix_const_iterator1>::difference_type operator-(const matrix_const_iterator1& oth) { return matrix_const_iterator<M>::pos1 - oth.pos1; }
	};

	template <typename M>
	class matrix_const_iterator2 : public matrix_const_iterator<M> {
	public:
		matrix_const_iterator2(M& mat, size_t pos1, size_t pos2) : matrix_const_iterator<M>(mat, pos1, pos2) {}
		matrix_const_iterator2& operator++() { ++matrix_const_iterator<M>::pos2; return *this; }
		typename std::iterator_traits<matrix_const_iterator2>::difference_type operator-(const matrix_const_iterator2& oth) { return matrix_const_iterator<M>::pos2 - oth.pos2; }
	};
}}

#endif