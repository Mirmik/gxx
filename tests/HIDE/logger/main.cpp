#include <gxx/log/logger2.h>
#include <gxx/log/target2.h>

//#include <gxx/log/targets/stdout.h>

gxx::log::stdout_target console_target;
gxx::log::logger syslog("syslog");

int main() {
	syslog.link(console_target, gxx::log::level::debug);

	syslog.debug("what {}", 3);
	syslog.debug("that {}", "port");
	syslog.info("I love {}", "you");
}
