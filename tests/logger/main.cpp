#include <thread>
#include <chrono>
#include <iostream>

#include <gxx/logger/logger.h>
#include <gxx/logger/targets/stdout.h>

gxx::log::stdout_target console_target;
gxx::log::logger logger("Console");

int main() {
	logger.set_pattern("Mirmik: {time}[{level}]{logger}| {msg}");
	logger.add_target(console_target);
	
	logger.debug("what {}", 3);
	logger.debug("that {}", "port");
	logger.info("I love {}", "you");
}