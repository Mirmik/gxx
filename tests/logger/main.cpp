#include <gxx/log/logger2.h>
//#include <gxx/log/targets/stdout.h>

//gxx::log::stdout_target console_target;
gxx::log::logger logger("Console");

int main() {
	//logger.set_pattern("Mirmik: {time}[{level}]{logger}| {msg}");
	//logger.add_target(console_target);

	//console_target.set_level(gxx::log::level::info);

	logger.debug("what {}", 3);
	logger.debug("that {}", "port");
	logger.info("I love {}", "you");
}
