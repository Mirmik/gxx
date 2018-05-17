#ifndef GXX_MATH_LINALG_H
#define GXX_MATH_LINALG_H

//Based on github.com/melax/sandbox/linalg

#include <cmath>	// For various unary math functions, such as std::sqrt
#include <cstdlib>	// For size_t
//#include <cstdint>// For implementing namespace linalg::aliases
#include <array>	// As std::array that used as basic type

namespace gxx { namespace linalg {

	template <typename T, size_t M> struct vec {
		T vars[M];

		constexpr vec() : vars() {} 

		constexpr vec(std::initializer_list<T> lst) : vars() {
			T* ptr = vars;
			for(auto val : lst) *ptr++ = val;
		} 
	};

	template <typename T, size_t M, size_t N> struct mat {
		vec<T, M> m_cols[N];

		constexpr mat() : m_cols() {}

		constexpr mat(std::initializer_list<vec<T,M>> lst)  {
			vec<T, M>* ptr = m_cols;
			for(const auto& val : lst) *ptr++ = val;	
		}

	};

}}


#endif