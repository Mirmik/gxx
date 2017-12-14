#include <iostream>
#include <gxx/geom/correction.h>

int main() {
	gxx::ngeom::line line({3,2,5,6}, {10,2,6,7});

	//gxx::println(line);
	//gxx::println(line.length());
	
	gxx::math::vector<float> corcoords(20);
	
	int count = 0;
	for (auto& ref: corcoords) { ref = count++;}
	
	//gxx::print(corcoords);

	auto table = gxx::math::matrix<float>::random(20, 2, -1, 1);

	gxx::ngeom::single_axis_correction_table<float> cortable(4, 0, corcoords, {1,2}, table);
	cortable.correction(line);

	//gxx::print(corcoords);
}