#ifndef GXX_MATH_LINALG_H
#define GXX_MATH_LINALG_H

#include <stdlib.h>
#include <utility>
#include <functional>

//Based on github.com/melax/sandbox/linalg

//#include <cmath>	// For various unary math functions, such as std::sqrt
//#include <cstdlib>	// For size_t
//#include <cstdint>// For implementing namespace linalg::aliases
//#include <array>	// As std::array that used as basic type

namespace gxx { namespace linalg {
	template <typename T, int M> struct vec {
		T 			elems[M];
		constexpr T& 			operator[](size_t i) 		{ return elems[i]; }
		constexpr const T& 	operator[](size_t i) const 	{ return elems[i]; }
	};

	template <typename T, int M, int N> struct mat {
		vec<T,M> 		cols[N];
		constexpr vec<T,M>& 		operator[](size_t i) 		{ return cols[i]; }
		constexpr const vec<T,M>&	operator[](size_t i) const 	{ return cols[i]; }
		template <size_t ... I> constexpr vec<T,M> __row(int i, std::index_sequence<I...>) { return { cols[I][i] ... }; }
		constexpr vec<T,M> row(int i) { return __row(i, std::make_index_sequence<N>()); }
		template <size_t ... I> constexpr vec<T,M> __row(int i, std::index_sequence<I...>) const { return { cols[I][i] ... }; }
		constexpr vec<T,M> row(int i) const { return __row(i, std::make_index_sequence<N>()); }
	};


    // Type traits for a binary operation involving linear algebra types, used for SFINAE on templated functions and operator overloads
    template<class A, class B> struct traits {};
    template<class T, int M       > struct traits<vec<T,M  >, vec<T,M  >> { typedef T scalar; typedef vec<T,M  > result; typedef vec<bool,M  > bool_result; typedef vec<decltype(+T()),M  > arith_result; };//typedef std::array<T,M> compare_as; };
    template<class T, int M       > struct traits<vec<T,M  >, T         > { typedef T scalar; typedef vec<T,M  > result; typedef vec<bool,M  > bool_result; typedef vec<decltype(+T()),M  > arith_result; };
    template<class T, int M       > struct traits<T,          vec<T,M  >> { typedef T scalar; typedef vec<T,M  > result; typedef vec<bool,M  > bool_result; typedef vec<decltype(+T()),M  > arith_result; };
    template<class T, int M, int N> struct traits<mat<T,M,N>, mat<T,M,N>> { typedef T scalar; typedef mat<T,M,N> result; typedef mat<bool,M,N> bool_result; typedef mat<decltype(+T()),M,N> arith_result; };//typedef std::array<T,M*N> compare_as; };
    template<class T, int M, int N> struct traits<mat<T,M,N>, T         > { typedef T scalar; typedef mat<T,M,N> result; typedef mat<bool,M,N> bool_result; typedef mat<decltype(+T()),M,N> arith_result; };
    template<class T, int M, int N> struct traits<T,          mat<T,M,N>> { typedef T scalar; typedef mat<T,M,N> result; typedef mat<bool,M,N> bool_result; typedef mat<decltype(+T()),M,N> arith_result; };
    template<class A, class B=A> using scalar_t = typename traits<A,B>::scalar; // Underlying scalar type when performing elementwise operations
    template<class A, class B=A> using result_t = typename traits<A,B>::result; // Result of calling a function on linear algebra types
    template<class A, class B=A> using bool_result_t = typename traits<A,B>::bool_result; // Result of a comparison or unary not operation on linear algebra types
    template<class A, class B=A> using arith_result_t = typename traits<A,B>::arith_result; // Result of an arithmetic operation on linear algebra types (accounts for integer promotion)

	namespace detail {
		template<class T, class F, int N, size_t ... I> 
		constexpr auto zip(const vec<T,N>& a, const vec<T,N>& b, F f, std::index_sequence<I...>) -> vec<decltype(f(T(),T())),N> {
			return { f(a[I],b[I]) ... };
		}
	}

	template<class T, class F, int N> 
	constexpr auto zip(const vec<T,N>& a, const vec<T,N>& b, F f) -> vec<decltype(f(T(),T())),N> {
		return detail::zip<T,F,N>(a,b,f,std::make_index_sequence<N>());
	}

	namespace detail {
		template<class T, class F, int N, int M, size_t ... I> 
		constexpr auto zip(const mat<T,N,M>& a, const mat<T,N,M>& b, F f, std::index_sequence<I...>) -> mat<decltype(f(T(),T())),N,M> {
			return { zip(a[I],b[I],f) ... };
		}
	}

	template<class T, class F, int N, int M> 
	constexpr auto zip(const mat<T,N,M>& a, const mat<T,N,M>& b, F f) -> mat<decltype(f(T(),T())),N,M> {
		return detail::zip<T,F,N,M>(a,b,f,std::make_index_sequence<M>());
	}

    template<class T, int M,        class F> constexpr auto map(const vec<T,M  > & a, F f) -> vec<decltype(f(T())),M  > { return zip(a, a, [f](T l, T) { return f(l); }); }
    template<class T, int M, int N, class F> constexpr auto map(const mat<T,M,N> & a, F f) -> mat<decltype(f(T())),M,N> { return zip(a, a, [f](T l, T) { return f(l); }); }

    template<class A, class B> constexpr arith_result_t<A,B> operator +  (const A & a, const B & b) { return zip(a, b, std::plus<scalar_t<A,B>>()); }
    template<class A, class B> constexpr arith_result_t<A,B> operator -  (const A & a, const B & b) { return zip(a, b, std::minus<scalar_t<A,B>>()); }
    template<class A, class B> constexpr arith_result_t<A,B> operator *  (const A & a, const B & b) { return zip(a, b, std::multiplies<scalar_t<A,B>>()); }
    template<class A, class B> constexpr arith_result_t<A,B> operator /  (const A & a, const B & b) { return zip(a, b, std::divides<scalar_t<A,B>>()); }



	//template<typename T, size_t M> constexpr vec<T,M> operator+(const vec<T,M>& a, const vec<T,M>& b) { return zip(a, b, [](auto a, auto b){return a+b;}); }
}}

//gxx::linalg operator+


#endif