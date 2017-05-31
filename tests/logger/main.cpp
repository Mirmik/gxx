#include <thread>
#include <chrono>
#include <iostream>
#include <gxx/logger/logger.h>
#include <gxx/logger/stdout.h>
#include <gxx/logger/linux_tcp_socket.h>
#include <gxx/debug/dprint.h>


gxx::log::stdout_target console_target;
gxx::log::spam_server_target spam_target(9876);
gxx::log::logger logger("Console");

int main() {
	spam_target.start(10);

	logger.set_pattern("[{level:U}] {msg}");
	logger.link(console_target);
	logger.link(spam_target);
	

	int i = 7;

	while(1) {
		logger.debug("what {}", i++);
		logger.debug("that {}", "port");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	};
}