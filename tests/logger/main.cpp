#include <iostream>
#include <gxx/logger/logger.h>
#include <gxx/logger/stdout.h>
#include <gxx/debug/dprint.h>

gxx::log::stdout_target console_target;
gxx::log::logger console;

int main() {
	console.link(console_target);

	console.debug("Mirmik {0:U}", "hack this");
}