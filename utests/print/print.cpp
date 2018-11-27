#include <gtest/gtest.h>
#include <gxx/print.h>

using namespace gxx::argument_literal;

TEST(print, print) {
	testing::internal::CaptureStdout();
	gxx::print("print");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "print");
}

TEST(print, format) {
	std::string out = gxx::format("format {} {} {}", "aaa", "bbb", "ccc");
	EXPECT_EQ(out, "format aaa bbb ccc");
}

TEST(print, fprint) {
	testing::internal::CaptureStdout();
	gxx::fprint("fprint {} {} {}", "aaa", "bbb", "ccc");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "fprint aaa bbb ccc");
}

TEST(print, fprint_named) {
	testing::internal::CaptureStdout();
	gxx::fprint("fprint {a} {b} {c}", "a"_a="aaa", "b"_a="bbb", "c"_a="ccc");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "fprint aaa bbb ccc");
}

TEST(print, fprint_zero_size_arglist) {
	testing::internal::CaptureStdout();
	gxx::fprint("zerosize");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "zerosize");
}

TEST(print, fprint_longstring) {
	testing::internal::CaptureStdout();
	gxx::fprint("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

TEST(print, number) {
	testing::internal::CaptureStdout();
	gxx::print(0.88);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "0.88000");
}

TEST(print, fprint_number) {
	testing::internal::CaptureStdout();
	gxx::fprint("double({})", 0.88);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "double(0.88000)");
}

TEST(print, integer) {
	testing::internal::CaptureStdout();
	gxx::print(0.88);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "0.88000");
}

TEST(print, fprint_integer) {
	testing::internal::CaptureStdout();
	gxx::fprint("integer({})", 42);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "integer(42)");
}