#ifndef MALGO_H
#define MALGO_H

#include <gxx/math/major.h>
#include <gxx/math/util.h>
#include <gxx/util/random.h>
#include <gxx/print.h>

namespace malgo {

template <typename T1, typename T2, typename T3> 		void vector_add(T1 A, T2 B, int n, T3 C) ;
template <typename T1, typename T2, typename T3> 		void vector_sub(T1 A, T2 B, int n, T3 C) ;
template <typename T1, typename T2, typename S>			void vector_scale(T1 A, int n, S s, T2 B);
template <typename T1, typename T2>						void vector_normalize(T1 A, int n, T2 B);

template<typename T, typename A = std::allocator<T>> class vector; 
template<typename T, typename O = gxx::math::row_major, typename A = std::allocator<T>> class matrix;

template<typename V>
class vector_basic : public gxx::array_printable<V> {
public:
	//vector_basic() = default;
	
	template<typename OV> V& operator+=(const OV& oth) { 
		V& self = *static_cast<V*>(this);
		malgo::vector_add(self.begin(), oth.begin(), self.size(), self.begin()); 
		return self;
	}

	template<typename OV> V& operator-=(const OV& oth) { 
		V& self = *static_cast<V*>(this);
		malgo::vector_sub(self.begin(), oth.begin(), self.size(), self.begin()); 
		return self;
	}

	void self_scale(double arg) { 
		V& self = *static_cast<V*>(this);
		malgo::vector_scale(self.begin(), self.size(), arg, self.begin()); 
	}

	void self_normalize() { 
		V& self = *static_cast<V*>(this);
		malgo::vector_normalize(self.begin(), self.size(), self.begin()); 
	}

	template <typename OV>
	auto operator+(const OV& b) const& { 
		const V& self = *static_cast<const V*>(this);
		vector<decltype(self[0] + b[0])> ret(self.size()); 
		malgo::vector_add(self.begin(), b.begin(), self.size(), ret.begin()); 
		return ret; 
	}

	template <typename OV>
	auto operator-(const OV& b) const& { 
		const V& self = *static_cast<const V*>(this);
		vector<decltype(self[0] - b[0])> ret(self.size()); 
		malgo::vector_sub(self.begin(), b.begin(), self.size(), ret.begin()); 
		return ret; 
	}
};

template<typename V, typename T>
class vector_compact_basic : public vector_basic<V> {
public:
	T* dat;
	size_t sz;

	CONSTREF_GETTER(size, sz);
	CONSTREF_GETTER(data, dat);
	
	vector_compact_basic(T* dat, size_t sz) : dat(dat), sz(sz) {}
	vector_compact_basic(const vector_compact_basic&) = default;
	vector_compact_basic(vector_compact_basic&&) = default;
	
	T& operator[](size_t i) { return dat[i]; }
	const T& operator[](size_t i) const { return dat[i]; }

	using iterator = T*;
	using const_iterator = T*;

	iterator begin() { return dat; }
	const iterator end() { return dat + sz; }
	const_iterator begin() const { return dat; }
	const const_iterator end() const { return dat + sz; }	
};

template<typename T, typename A>
class vector : public vector_compact_basic<vector<T>, T> {
	using parent = vector_compact_basic<vector<T>,T>;
	A alloc;
public:
	vector(size_t sz) : parent(alloc.allocate(sz), sz) {}
	vector(const gxx::objbuf<T>& buf) : parent(alloc.allocate(buf.size()), buf.size()) { std::copy(buf.begin(), buf.end(), parent::begin()); }
	vector(const std::initializer_list<T>& lst) : parent(alloc.allocate(lst.size()), lst.size()) { std::copy(lst.begin(), lst.end(), parent::begin()); }
	vector(const vector& oth) : parent(alloc.allocate(oth.size()), oth.size()) { std::copy(oth.begin(), oth.end(), parent::begin()); }	
	vector(vector&& oth) : parent(oth.data(), oth.size()) { oth.dat = nullptr; oth.sz = 0; }
	~vector() { alloc.deallocate(parent::dat, parent::sz); parent::dat = nullptr; parent::sz = 0; }

	using parent::operator+;
	vector operator+(vector&& b) const& { vector ret(std::move(b)); malgo::vector_add(parent::begin(), ret.begin(), parent::size(), ret.begin()); return ret; }
	vector operator+(const vector& b) && { vector ret(std::move(*this)); malgo::vector_add(ret.begin(), b.begin(), b.size(), ret.begin()); return ret; }

	using parent::operator-;
	vector operator-(vector&& b) const& { vector ret(std::move(b)); malgo::vector_sub(parent::begin(), ret.begin(), parent::size(), ret.begin()); return ret; }
	vector operator-(const vector& b) && { vector ret(std::move(*this)); malgo::vector_sub(ret.begin(), b.begin(), b.size(), ret.begin()); return ret; }
};

template<typename T>
class vector_compact_proxy : public vector_compact_basic<vector_compact_proxy<T>, T> {
public:
	using parent = vector_compact_basic<vector_compact_proxy<T>,T>;
	vector_compact_proxy(T* dat, size_t sz) : parent(dat, sz) {}
};

template<typename T>
struct step_ptr {
	T* ptr;
	int step;
	step_ptr(T* ptr, int step) : ptr(ptr), step(step) {}
	step_ptr& operator++() { ptr += step; return *this; }
	step_ptr operator++(int) { auto ret = *this; ptr += step; return ret; }
	T& operator*() { return *ptr; }
	bool operator!=(const step_ptr& oth) { return ptr != oth.ptr; }
};

template<typename T>
struct const_step_ptr {
	const T* ptr;
	int step;
	const_step_ptr(const T* ptr, int step) : ptr(ptr), step(step) {}
	const_step_ptr& operator++() { ptr += step; return *this; }
	const_step_ptr operator++(int) { auto ret = *this; ptr += step; return ret; }
	const T& operator*() { return *ptr; }
	bool operator!=(const const_step_ptr& oth) { return ptr != oth.ptr; }
};

template<typename T>
class vector_stepped_proxy : public vector_basic<vector_stepped_proxy<T>> {
public:
	T* dat;
	size_t sz;
	size_t step;
	CONSTREF_GETTER(size, sz);
	CONSTREF_GETTER(data, dat);
	T& operator[](size_t i) { return dat[i * step]; }
	const T& operator[](size_t i) const { return dat[i * step]; }
	using iterator = step_ptr<T>;
	using const_iterator = const_step_ptr<T>;
	using parent = vector_basic<vector_compact_proxy<T>>;
	vector_stepped_proxy(T* dat, size_t sz, size_t step) : dat(dat), sz(sz), step(step) {}
	iterator begin() { return iterator(dat, step); }
	const iterator end() { return iterator(dat + step * sz, step); }
	const_iterator begin() const { return const_iterator(dat, step); }
	const const_iterator end() const { return const_iterator(dat + step * sz, step); }	
};

template <typename T>
struct iterator_matrix_compact {
	T* dat;
	size_t sz2;
	iterator_matrix_compact(T* dat, size_t sz2) : dat(dat), sz2(sz2) {}
	T* begin() { return dat; }
	T* const end() { return dat + sz2; }
	iterator_matrix_compact& operator++() { dat += sz2; return *this; }
	iterator_matrix_compact operator++(int) { auto ret = *this; dat += sz2; return ret; }
	vector_compact_proxy<T> operator*() { return vector_compact_proxy<T>(dat, sz2); }
	bool operator!=(const iterator_matrix_compact& oth) { return dat != oth.dat; }
};

template <typename T>
struct iterator_matrix_compact_column {
	T* dat;
	size_t sz1;
	size_t step;
	iterator_matrix_compact_column(T* dat, size_t sz1, size_t step) : dat(dat), sz1(sz1), step(step) {}
	step_ptr<T> begin() { return step_ptr<T>(dat, step); }
	T* const end() { return step_ptr<T>(dat + sz1 * step, step); }
	iterator_matrix_compact_column& operator++() { ++dat; return *this; }
	iterator_matrix_compact_column operator++(int) { auto ret = *this; ++dat; return ret; }
	vector_stepped_proxy<T> operator*() { return vector_stepped_proxy<T>(dat, sz1, step); }
	bool operator!=(const iterator_matrix_compact_column& oth) { return dat != oth.dat; }

};

template <typename M>
class matrix_basic : public gxx::matrix_printable<M> {
public:

};

template<typename M, typename T, typename O>
class matrix_compact_basic : public matrix_basic<M> {
public:
	T* dat;
	size_t sz1;
	size_t sz2;

	CONSTREF_GETTER(data, dat);
	CONSTREF_GETTER(size1, sz1);
	CONSTREF_GETTER(size2, sz2);

	matrix_compact_basic(T* dat, size_t sz1, size_t sz2) : dat(dat), sz1(sz1), sz2(sz2) {}
	void clean() { memset(dat, 0, sz1 * sz2 * sizeof(T)); }

	T& operator()(size_t pos1, size_t pos2) { return gxx::math::major_accessor<T*,O>::ref(dat, pos1, pos2, sz1, sz2); }
	const T& operator()(size_t pos1, size_t pos2) const { return gxx::math::major_accessor<const T*,O>::const_ref(dat, pos1, pos2, sz1, sz2); }

	vector_compact_proxy<T> row(size_t i) { return vector_compact_proxy<T>(dat + i * sz2, sz2); }			// TODO COLUMN_ORDER
	vector_stepped_proxy<T> column(size_t i) { return vector_stepped_proxy<T>(dat + i, sz1, sz2); }		// TODO COLUMN_ORDER

	iterator_matrix_compact<T> begin_row() { return iterator_matrix_compact<T>(dat, sz2); }
	const iterator_matrix_compact<T> end_row() { return iterator_matrix_compact<T>(dat + sz1 * sz2, sz2); }

	iterator_matrix_compact_column<T> begin_column() { return iterator_matrix_compact_column<T>(dat, sz1, sz2); }
	const iterator_matrix_compact_column<T> end_column() { return iterator_matrix_compact_column<T>(dat + sz2, sz1, sz2); }
};

template<typename T, typename O, typename A>
class matrix : public matrix_compact_basic<matrix<T,O>,T,O> {
	A alloc;
public:
	using parent = matrix_compact_basic<matrix<T,O>,T,O>;

	matrix(size_t sz1, size_t sz2) : parent(alloc.allocate(sz1*sz2), sz1, sz2) {}
};







template <typename T1, typename T2, typename T3>
void vector_add(T1 A, T2 B, int n, T3 C) {
	while(n--) *C++ = *A++ + *B++;
}

template <typename T1, typename T2, typename T3>
void vector_sub(T1 A, T2 B, int n, T3 C) {
	while(n--) *C++ = *A++ - *B++;
}

//template <typename T1, typename T2>
//void vector_self_add(T1 A, T2 B, int n) {
//	while(n--) *A++ += *B++;
//}
//
//template <typename T1, typename T2>
//void vector_self_sub(T1 A, T2 B, int n) {
//	while(n--) *A++ -= *B++;
//}

template <typename T1, typename T2, typename T3>
void matrix_add(const T1 *A, const T2 *B, int m, int n, T3 *C) {
	vector_add(A, B, m*n, C);
}

template <typename T1, typename T2>
void vector_copy( const T1* A, int n, T2* B) {
	while(n--) *B++ = *A++;
}

template <typename T1, typename T2>
void matrix_copy( const T1* A, int m, int n, T2* B) {
	vector_copy(A,m*n,B);
}

template <typename T1, typename T2>
void vector_copy_uncompact( T1 A, int n, T2 B, int as, int bs) {
	while(n--) { 
		*B = *A;
		A += as;
		B += bs;
	}
}


template <typename T>
void vector_random( T* A, int n, auto min, auto max) {
	while(n--) { 
		*A++ = gxx::random_minmax<T>(min, max);
		//gxx::println(*(A-1));
	}
}

template <typename T1, typename T2, typename T3>
void matrix_mux(T1* A, T2* B, int m, int p, int n, T3* C)
{
	// A = input matrix (m x p)
	// B = input matrix (p x n)
	// m = number of rows in A
	// p = number of columns in A = number of rows in B
	// n = number of columns in B
	// C = output matrix = A*B (m x n)
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			C[n*i+j]=0;
			for (k=0;k<p;k++)
				C[n*i+j]= C[n*i+j]+A[p*i+k]*B[n*k+j];
		}
}

template <typename T>
auto vector_sqr(T V, size_t n) {
	double sum;
	while(n--) {
		auto tmp = *V++;
		sum += tmp * tmp;
	}
	return sum;
}

template <typename T>
auto vector_abs(T v, size_t n) {
	return sqrt(vector_sqr(v,n));
}

float vector_quick_invabs(float* v, size_t n) {
	return quick_rsqrt(vector_abs(v,n));
}

template <typename T1, typename T2, typename S>
void vector_scale(T1 A, int n, S s, T2 B) {
	while(n--) *B++ = *A++ * s;
}

template <typename T1, typename T2, typename S>
void vector_rscale(T1 A, int n, S s, T2 B) {
	while(n--) *B++ = *A++ / s;
}

//template <typename T, typename S>
//void vector_self_scale(T* A, int n, S s) {
//	while(n--) *A++ *= s;
//}
//
//template <typename T, typename S>
//void vector_self_rscale(T* A, int n, S s) {
//	while(n--) *A++ /= s;
//}

template <typename T1, typename T2>
void vector_normalize(T1 A, size_t n, T2 B) {
	vector_rscale(A, n, vector_abs(A,n), B);
}

//template <typename T>
//void vector_self_normalize(T A, size_t n) {
//	vector_self_rscale(A, n, vector_abs(A,n));
//}

void vector_quick_normalize(float* A, size_t n, float* B) {
	vector_scale(A, n, vector_quick_invabs(A,n), B);
}

/*
template <typename T1, typename T2, typename T3>
void matrix_sub(const T1 *A, const T2 *B, int m, int n, T3 *C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A-B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]-B[n*i+j];
};


template <typename T1, typename T2, typename T3>
void matrix_scale(const T1* A, const T2 k, int m, int n, T3* C)
{
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			C[n*i+j] = A[n*i+j]*k;
}




//Matrix Inversion Routine
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in 
//	 NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
template <typename T1>
void matrix_inv(const T1* C, int m, int n, T1* A)
{	// C = input matrix 
	// A = result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k,i,j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	double tmp;		// used for finding max value and making column swaps

	for (i = 0 ; i < m; i++)
		for (j = 0 ; j < n; j++)
			A[i*n+j]=C[i*n+j];

	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (abs(A[i*n+k]) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = abs(A[i*n+k]);
				pivrow = i;
			}
		}

		// check for singular matrix
		if (A[pivrow*n+k] == 0.0f)
		{
			prln("Inversion failed due to singular matrix");
			return;
		}

		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = A[k*n+j];
				A[k*n+j] = A[pivrow*n+j];
				A[pivrow*n+j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)

		tmp = 1.0f/A[k*n+k];	// invert pivot element
		A[k*n+k] = 1.0f;		// This element of input matrix becomes result matrix

		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			A[k*n+j] = A[k*n+j]*tmp;
		}

		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = A[i*n+k];
				A[i*n+k] = 0.0f;  // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					A[i*n+j] = A[i*n+j] - A[k*n+j]*tmp;
				}
			}
		}
	}

	// Done, now need to undo pivot row swaps by doing column swaps in reverse order
	for (k = n-1; k >= 0; k--)
	{
		if (pivrows[k] != k)
		{
			for (i = 0; i < n; i++)
			{
				tmp = A[i*n+k];
				A[i*n+k] = A[i*n+pivrows[k]];
				A[i*n+pivrows[k]] = tmp;
			}
		}
	}
	return;
};








template <typename T1>
void matrix_exp(const T1* a, int n, T1* C)
{
	int i, j, k, ii;
   T1 am, em, emi;
   T1 w[n*n];

   T1 wm[n*n];
 
     em = 0.;
     for( i = 0; i < n; i++ ){
       for( j = 0; j < n; j++ ){
	 C[i*n+j] = 0;
	 wm[i*n+j] = 0;
	 am = abs(a[i*n+j]);
	 em = max(am,em);
       }
       C[i*n+i] = 1;
       wm[i*n+i] = 1;
     }
     emi = 1;
     ii = 0;
     while( emi > 0.1e-15 ){
       ii++;
       if( ii >= 50 ) break;
       emi = 0.;
       for( j = 0; j < n; j++ ){
	 for( i = 0; i < n; i++ )
	   w[i] = wm[i*n+j];
	 for( i = 0; i < n; i++ ){
	   wm[i*n+j] = 0.;
	   for( k = 0; k < n; k++ )
	     wm[i*n+j] += a[i*n+k] * w[k];
	 }
       }
       for( i = 0; i < n; i++ )
	 for( j = 0; j < n; j++ ){
	   wm[i*n+j] /= (double)ii;
	   C[i*n+j] += wm[i*n+j];
	   am = abs(wm[i*n+j]);
	   emi = max(am,emi);
	 }
     }
  
};



//Matrix Transpose Routine
template <typename T1, typename T2>
void matrix_transpose( const T1* A, int n, int m, T2* C)
{
	// A = input matrix (m x n)
	// m = number of rows in A
	// n = number of columns in A
	// C = output matrix = the transpose of A (n x m)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[m*j+i]=A[n*i+j];
}*/


}

#endif 