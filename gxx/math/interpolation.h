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
		vector<Type> linear_interpolation_matrix_rows(Type coord, const VecCoord& vec, const Matrix& mat) {
			int anum;
			int num;
			auto lower = std::lower_bound(vec.begin(), vec.end(), coord);
			if (lower == vec.end()) { 
				anum = vec.size() - 2; 
			}
			else {
				num = std::distance(vec.begin(), lower) - 1;
			}			

			vector<Type> ret = linear_interpolation_2point(coord, vec[anum], vec[anum+1], mat.row(anum), mat.row(anum+1));

			gxx::vprintln("vector", vec);
			gxx::vprintln("matrix", mat);
			gxx::vprintln("coord", coord);
			gxx::println(num);

			return vector<Type>(1);
		}


	}
}

#endif