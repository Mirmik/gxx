#include <gxx/math/interval.h>

int main() {
	gxx::math::interval<double> i1(2, 10);
	gxx::math::interval<double> i2(4, 6);
	gxx::math::interval<double> i3(8, 10);
	gxx::math::interval<double> i4(8, 11);
	gxx::math::interval<double> i5(2, 4);
	gxx::math::interval<double> i6(1, 4);
	gxx::math::interval<double> i7(11, 47);
	gxx::math::interval<double> i8(1, 2);

	GXX_PRINT(i1.difference(i2));
	GXX_PRINT(i1.difference(i3));
	GXX_PRINT(i1.difference(i4));
	GXX_PRINT(i1.difference(i5));
	GXX_PRINT(i1.difference(i6));
	GXX_PRINT(i1.difference(i7));
	GXX_PRINT(i1.difference(i8));

	GXX_PRINT(i1.intersect(i2));
	GXX_PRINT(i1.intersect(i3));
	GXX_PRINT(i1.intersect(i4));
	GXX_PRINT(i1.intersect(i5));
	GXX_PRINT(i1.intersect(i6));
	GXX_PRINT(i1.intersect(i7));
	GXX_PRINT(i1.intersect(i8));

	GXX_PRINT(i1.combine(i2));
	GXX_PRINT(i1.combine(i3));
	GXX_PRINT(i1.combine(i4));
	GXX_PRINT(i1.combine(i5));
	GXX_PRINT(i1.combine(i6));
	GXX_PRINT(i1.combine(i7));
	GXX_PRINT(i1.combine(i8));

	auto a = gxx::math::interval<double>(1,2);
	auto b = gxx::math::interval<double>(2,3);

	GXX_PRINT(a.intersect(b));
	GXX_PRINT(a.difference(b));
	GXX_PRINT(b.difference(a));
	GXX_PRINT(a.combine(b));

	gxx::math::interval_union<double> ints1{{1,2}, {2,4}, {7,29}, {51,57}};
	gxx::math::interval_union<double> ints2{{6,8}, {28,33}, {44,52}, {53,55}};

	//gxx::math::interval_union<double> ints1{{1,3}, {4,7}};
	//gxx::math::interval_union<double> ints2{{2,5}, {6,8}};
	GXX_PRINT(ints1);
	GXX_PRINT(ints2);
	GXX_PRINT(ints1.combine(ints2));
	GXX_PRINT(ints1.intersect(ints2));
	GXX_PRINT(ints1.difference(ints2));
	GXX_PRINT(ints2.difference(ints1));


	auto c = gxx::math::interval<double>(1,3);
	auto d = gxx::math::interval<double>(2,4);

	gxx::println(c.simple_symmetric_difference(d));
	gxx::println(c.divide(2));
}