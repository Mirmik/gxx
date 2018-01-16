#include <gtest/gtest.h>
#include <gxx/print.h>

TEST(Print, print) {
	testing::internal::CaptureStdout();
	gxx::print("Mirmik");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Mirmik");
}

TEST(Print, number) {
	testing::internal::CaptureStdout();
	gxx::print(0.88);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "0.88000");
}

TEST(Print, format_number) {
	testing::internal::CaptureStdout();
	gxx::fprint("double({})", 0.88);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "double(0.88000)");
}