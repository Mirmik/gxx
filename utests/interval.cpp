#include <gtest/gtest.h>
#include <gxx/math/interval.h>

TEST(Interval, combine) {
	using iu = gxx::math::interval_union<double>;

	iu u0 = {{1, 11}, {12, 56}};
	
	iu u1 = {{11, 12}, {53, 80}};
	iu u1res = {{1, 80}};

	iu u2 = {{11.5, 12}, {57, 80}};
	iu u2res = {{1, 11}, {11.5, 56}, {57, 80}};

	/*gxx::println(u0.combine(u1));
	gxx::println(u1res);
	gxx::println(u0.combine(u2));
	gxx::println(u2res);*/

	EXPECT_EQ(u0.combine(u1), u1res);
	EXPECT_EQ(u0.combine(u2), u2res);
}

TEST(Interval, difference) {
	using iu = gxx::math::interval_union<double>;

	iu u0 = {{1, 3}};

	iu u1 = {{0.5, 2}};
	iu u1res = {{2, 3}};

	iu u2 = {{1.5, 2}, {2.5, 2.7}};
	iu u2res = {{1, 1.5}, {2, 2.5}, {2.7, 3}};

	//gxx::println(u0.difference(u1));
	//gxx::println(u1res);
	//gxx::println(u0.difference(u2));
	//gxx::println(u2res);

	EXPECT_EQ(u0.difference(u1), u1res);
	EXPECT_EQ(u0.difference(u2), u2res);
}

TEST(Interval, intersect) {
	using iu = gxx::math::interval_union<double>;

	iu u0 = {{1, 3}};

	iu u1 = {{0.5, 2}};
	iu u1res = {{1, 2}};

	iu u2 = {{1.5, 2}, {2.5, 2.7}, {2.8, 4}};
	iu u2res = {{1.5, 2}, {2.5, 2.7}, {2.8, 3}};

	/*gxx::println(u0.intersect(u1));
	gxx::println(u1res);
	gxx::println(u0.intersect(u2));
	gxx::println(u2res);*/

	EXPECT_EQ(u0.intersect(u1), u1res);
	EXPECT_EQ(u0.intersect(u2), u2res);
}