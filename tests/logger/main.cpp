#include <thread>
#include <chrono>
#include <iostream>
#include <gxx/logger/logger.h>
#include <gxx/logger/stdout.h>
//#include <gxx/logger/linux_tcp_socket.h>
#include <gxx/debug/dprint.h>
#include <gxx/debug/testclass.h>

#include <gxx/logger/loader_manager.h>
#include <gxx/util/init_priority.h>

PRIORITY_INITIALIZATION gxx::log::loader_manager logManager("logsettings.json");

TestClass test;

gxx::log::stdout_target console_target;
//gxx::log::spam_server_target spam_target(9876);
gxx::log::logger logger("Console");

int main() {
	//logManager.parse_settings();
	logManager.registry(logger);


	//spam_target.start(10);

	logger.set_pattern("{time}[{level:U}]{logger} {msg}");
	logger.link(console_target);
//	logger.link(spam_target);
	
	
	while(1) {
		logger.debug("what {}", 3);
		logger.debug("that {}", "port");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	};
}