#include <gxx/math/interval.h>

int main() {
	gxx::math::interval<double> i1(2, 10);
	gxx::math::interval<double> i2(4, 6);
	gxx::math::interval<double> i3(8, 10);
	gxx::math::interval<double> i4(8, 11);
	gxx::math::interval<double> i5(2, 4);
	gxx::math::interval<double> i6(1, 4);
	gxx::math::interval<double> i7(11, 47);

	GXX_PRINT(i1.difference(i2));
	GXX_PRINT(i1.difference(i3));
	GXX_PRINT(i1.difference(i4));
	GXX_PRINT(i1.difference(i5));
	GXX_PRINT(i1.difference(i6));
	GXX_PRINT(i1.difference(i7));

	GXX_PRINT(i1.intersect(i2));
	GXX_PRINT(i1.intersect(i3));
	GXX_PRINT(i1.intersect(i4));
	GXX_PRINT(i1.intersect(i5));
	GXX_PRINT(i1.intersect(i6));
	GXX_PRINT(i1.intersect(i7));

	GXX_PRINT(i1.combine(i2));
	GXX_PRINT(i1.combine(i3));
	GXX_PRINT(i1.combine(i4));
	GXX_PRINT(i1.combine(i5));
	GXX_PRINT(i1.combine(i6));
	GXX_PRINT(i1.combine(i7));

	auto a = gxx::math::interval<double>(1,2);
	auto b = gxx::math::interval<double>(2,3);

	GXX_PRINT(a.intersect(b));
	GXX_PRINT(a.difference(b));
	GXX_PRINT(b.difference(a));
	GXX_PRINT(a.combine(b));

	gxx::math::interval_union<double> ints1{{1,2}, {2,4}, {7,29}, {51,57}};
	gxx::math::interval_union<double> ints2{{6,8}, {28,33}, {44,52}};

	//gxx::math::interval_union<double> ints1{{1,3}, {4,7}};
	//gxx::math::interval_union<double> ints2{{2,5}, {6,8}};
	GXX_PRINT(ints1);
	GXX_PRINT(ints2);
	GXX_PRINT(ints1.combine(ints2));
	GXX_PRINT(ints1.intersect(ints2));
	//GXX_PRINT(ints2.combine(ints1));

	//auto group = gxx::math::interval_union<double>::find_intersected_group(ints1.vec.begin(), ints1.vec.end(), ints2.vec.begin(), ints2.vec.end());

	/*auto ait = ints1.vec.begin();
	auto eait = ints1.vec.end();
	auto bit = ints2.vec.begin();
	auto ebit = ints2.vec.end();
	for(; ait != eait && bit != ebit;) {
		auto ret = gxx::math::interval_union<double>::find_intersected_group(ait, eait, bit, ebit);
		ait = ret.end_ait;
		bit = ret.end_bit;

		gxx::println("res_a");
		for (auto it = ret.begin_ait; it != ret.end_ait; ++it) { gxx::println(*it); }
		gxx::println("res_b");
		for (auto it = ret.begin_bit; it != ret.end_bit; ++it) { gxx::println(*it); }
	}*/
}