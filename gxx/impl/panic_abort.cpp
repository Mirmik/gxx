#include <gxx/panic.h>
#include <gxx/debug/dprint.h>
#include <stdlib.h>

namespace gxx {
	void panic(const char* str) {
		dprln(str);
		abort();
	}
}