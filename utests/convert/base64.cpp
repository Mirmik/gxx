#include <gtest/gtest.h>
#include <gxx/util/base64.h>

TEST(base64, equal) {
	std::string input;
	EXPECT_EQ(input, gxx::base64_decode(gxx::base64_encode(input)));
}
