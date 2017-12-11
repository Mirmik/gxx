#include <gxx/math/matrix.h>
#include <gxx/util/random.h>

int main() {
	gxx::math::matrix mat = 	gxx::math::matrix::diagonal({3,5,6});
	gxx::math::matrix mat2 = 	gxx::math::matrix::diagonal({3,7,6});
	gxx::math::matrix rmat = 	gxx::math::matrix::random(3,4,8.9,16);

	mat(2,1) = 45;
	gxx::print(rmat);
	//gxx::print(gxx::math::matrix::identity(5));

}