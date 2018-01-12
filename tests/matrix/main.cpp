#include <gxx/math/malgo.h>

int main() {
	malgo::matrix<float> mat(3,3);

	mat(1,1) = 3;
	mat(1,2) = 8;

	gxx::print(mat);
}