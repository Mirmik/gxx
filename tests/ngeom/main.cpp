#include <iostream>
#include <gxx/geom/ncurve.h>
#include <gxx/math/matrix.h>

int main() {
	gxx::ngeom::line line({3,2,5,6}, {10,2,6,7});

	gxx::println(line);
	gxx::println(line.length());
	
	gxx::math::vector<float> corcoords(20);
	int count = 0;
	for (auto& ref: corcoords) { ref = count++;}

	auto cortable = gxx::math::matrix<float>::random(20, 2, -1, 1);

	gxx::ngeom::correction_for_one_axis(line, 0, corcoords, {1,2}, cortable);

	//gxx::print(corcoords);
}