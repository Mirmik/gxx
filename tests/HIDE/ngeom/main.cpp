#include <iostream>
#include <gxx/geom/correction.h>
//#include <gxx/math/interpolation.h>

//#include <gxx/math/matrix.h>

#include <gxx/geom/ncurve.h>

int main() {
	gxx::ngeom::line l({0.5,1,2.8,3}, {4.5,4,5,6});
	
	std::vector<double> corcoords(5);
	int count = 0;
	for (auto& ref: corcoords) { ref = count++;}
	
	std::vector<double> table(5 * 2);
	malgo::vector_random(table.data(), table.size(), -1, 1);

	//table[0] = 0; 
	//table[1] = 0;
	//table[2] = 1; 
	//table[3] = 1;
	//table[4] = 2; 
	//table[5] = 2;
	//table[6] = 3; 
	//table[7] = 3;
	//table[8] = 4; 
	//table[9] = 4;

	gxx::ngeom::single_axis_correction_table<double> cortable(4, 0, corcoords, {1,2}, table);
	auto ml = cortable.correction(l);

	gxx::println(ml);

	malgo::vector<int> v1 {3, 6, 8};
	malgo::vector<int> v2 {3, 6, 9};

	gxx::println(v1 + v2);

	malgo::matrix<int> m(3,3); 
	m.clean();

	m.row(1)[2] = 33;
	for (auto& r : m.column(1)) {
		r = 55;
	}

	for (auto r = m.begin_column(); r != m.end_column(); ++r) {
		gxx::println(*r);
	}
	
	gxx::println(m);




}