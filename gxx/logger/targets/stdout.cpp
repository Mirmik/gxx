#include <gxx/logger/targets/stdout.h>

void gxx::log::stdout_target::log(const char* str) {
	std::cout << str << '\n';
}