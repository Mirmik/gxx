#include <gxx/logger/stdout.h>

void gxx::log::stdout_target::log(const char* str) {
	io.print(str);
}