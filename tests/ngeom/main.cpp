#include <iostream>
#include <gxx/geom/correction.h>
#include <gxx/math/interpolation.h>

int main() {
	/*gxx::ngeom::line line({3.4,0,0,0}, {10.3,0,0,0});

	//gxx::println(line);
	//gxx::println(line.length());
	
	gxx::math::vector<float> corcoords(20);
	
	int count = 0;
	for (auto& ref: corcoords) { ref = count++;}
	
	//gxx::print(corcoords);

		float n = 0;
	//auto table = gxx::math::matrix<float>::random(20, 2, -1, 1);
	auto table = gxx::math::matrix<float>(20, 2);
	for (auto it1 = table.begin1(); it1 != table.end1(); ++it1) {
		for (auto it2 = it1.begin(); it2 != it1.end(); ++it2) {
			*it2 = n;
		}
			n += 0.1;
	}
		
	gxx::ngeom::single_axis_correction_table<float> cortable(4, 0, corcoords, {1,2}, table);
	cortable.correction(line);*/

	//gxx::print(corcoords);

	gxx::math::vector<float> v1({1,0,1});
	gxx::math::vector<float> v2({2,4,3});

	gxx::print(gxx::math::linear_interpolation_2point<float>(1.5, v1[0], v2[0], v1, v2));
	
}