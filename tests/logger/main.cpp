#include <thread>
#include <chrono>
#include <iostream>

#include <gxx/log/logger.h>
#include <gxx/log/targets/stdout.h>

gxx::log::stdout_target console_target;
gxx::log::logger logger("Console");

int main() {
	logger.set_pattern("Mirmik: {time}[{level}]{logger}| {msg}");
	logger.add_target(console_target);

	logger.debug("what {}", 3);
	logger.debug("that {}", "port");
	logger.info("I love {}", "you");
}
