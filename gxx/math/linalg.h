#ifndef GXX_MATH_LINALG_H
#define GXX_MATH_LINALG_H

#include <stdlib.h>
#include <utility>

//Based on github.com/melax/sandbox/linalg

//#include <cmath>	// For various unary math functions, such as std::sqrt
//#include <cstdlib>	// For size_t
//#include <cstdint>// For implementing namespace linalg::aliases
//#include <array>	// As std::array that used as basic type

namespace gxx { namespace linalg {
	template <typename T, int M> struct vec {
		T elems[M];
		T& operator[](size_t i) { return elems[i]; }
		const T& operator[](size_t i) const { return elems[i]; }
	};

	template <typename T, int M, int N> struct mat {
		vec<T,M> cols[N];
		T& operator[](size_t i) { return cols[i]; }
		const T& operator[](size_t i) const { return cols[i]; }
	};

	namespace detail {
		template<class T, class F, int N, size_t ... I> 
		auto zip(const vec<T,N>& a, const vec<T,N>& b, F f, std::index_sequence<I...>) -> vec<decltype(f(T(),T())),N> {
			return { f(a[I],b[I]) ... };
		}
	}

	template<class T, class F, int N> 
	auto zip(const vec<T,N>& a, const vec<T,N>& b, F f) -> vec<decltype(f(T(),T())),N> {
		return detail::zip<T,F,N>(a,b,f,std::make_index_sequence<N>());
	}
}}


#endif