#ifndef MALGO_H
#define MALGO_H

#include <gxx/math/util.h>
#include <gxx/util/random.h>

namespace malgo {

template <typename T1, typename T2, typename T3>
void vector_add(const T1 *A, const T2 *B, int n, T3 *C) {
	while(n--) *C++ = *A++ + *B++;
}

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
void vector_copy_uncompact( const T1* A, int n, T2* B, int as, int bs) {
	while(n--) { 
		*B = *A;
		A += as;
		B += bs;
	}
}


template <typename T>
void vector_random( T* A, int n, auto min, auto max) {
	while(n--) *A++ = gxx::random_minmax<T>(min, max);
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
T vector_sqr(T* V, size_t n) {
	float sum;
	while(n--) {
		auto tmp = *V++;
		sum += tmp * tmp;
	}
	return sum;
}

template <typename T>
auto vector_abs(T* v, size_t n) {
	return sqrt(vector_sqr(v,n));
}

float vector_quick_invabs(float* v, size_t n) {
	return quick_rsqrt(vector_abs(v,n));
}

template <typename T, typename S>
void vector_scale(T* A, int n, S s, T* B) {
	while(n--) *B++ = *A++ * s;
}

template <typename T>
void vector_normalize(T* A, size_t n, T* B) {
	vector_rscale(A, n, vector_abs(A,n), B);
}

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
	float tmp;		// used for finding max value and making column swaps

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
	   wm[i*n+j] /= (float)ii;
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