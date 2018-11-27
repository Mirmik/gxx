#include <gtest/gtest.h>
#include <gxx/print.h>
#include <gxx/log/logger.h>
#include <gxx/log/targets/stdout.h>

using namespace gxx::argument_literal;

TEST(print, log) {
	testing::internal::CaptureStdout();

	gxx::log::logger logger("syslog");
	gxx::log::stdout_target target;

	logger.link(target);
	logger.info("HelloWorld {}", 33);

	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "[info]syslog: HelloWorld 33\n");
}