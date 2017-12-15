#ifndef GXX_INTERPOLATION_H
#define GXX_INTERPOLATION_H

#include <gxx/math/vector.h>

namespace gxx {
	namespace math {
		template<typename Type, typename Coords> 
		vector<Type> linear_interpolation_2point(Type coord, Type ac, Type bc, const Coords& a, const Coords& b) {
			return a + (b - a).scale((coord - ac) / (bc - ac)); 
		}

		template<typename Type, typename Matrix, typename VecCoord> 
		vector<Type> linear_interpolation(Type coord, const VecCoord& vec, const Matrix& mat) {

		}
	}
}

#endif