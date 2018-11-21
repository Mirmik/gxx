#include <gtest/gtest.h>
#include <gxx/util/math.h>

TEST(float_operations, isint) {
	EXPECT_EQ(isint(1.5), false);
	EXPECT_EQ(isint(1), true);
	EXPECT_EQ(isint(1412341), true);
	EXPECT_EQ(isint(141324.8), false);
	EXPECT_EQ(isint(11234), true);
	EXPECT_EQ(isint(1112313), true);
	EXPECT_EQ(isint(1112313.000000), true);
	EXPECT_EQ(isint(1123.43241), false);
	EXPECT_EQ(isint(1432141), true);
	EXPECT_EQ(isint(142134.89427342134), false);

	EXPECT_EQ(isint(-142134.89427342134), false);
	EXPECT_EQ(isint(-142134), true);
	EXPECT_EQ(isint(-142134.0000), true);
	EXPECT_EQ(isint(-142134.00001 + 0.00001), true);
}
