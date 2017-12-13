#include <gxx/math/matrix.h>
#include <gxx/math/vector.h>
#include <gxx/util/random.h>

#include <gxx/math/fixed.h>

int main() {
	//gxx::math::vector<float> corpoints(20);
	//auto cormatrix = gxx::math::matrix<float>::random(3, 20, -0.1, 0.1);

	//gxx::print(cormatrix);

	//for (int i = 0; i < 20; i++) {
	//	corpoints(i) = i;
	//}

	//float start = 5.7;
	//float stop = 16.3;

	gxx::math::matrix<float> mat(3,3);

	mat(1,1) = 3;
	mat(1,2) = 8;

	gxx::println(mat);
}