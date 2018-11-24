#include <gtest/gtest.h>
#include <gxx/debug/dprint.h>

TEST(debug, strlen) {
	EXPECT_EQ(debug_strlen("HelloWorld"), 10);
}
