#ifndef GXX_PANIC_H
#define GXX_PANIC_H

#include <gxx/util/location.h>
#include <cstring>
#include <cstdio>

namespace gxx {
	void panic(const char* str);

	static inline void panic_not_supported(location loc) {
		char buf [128];
		sprintf(buf, "FunctionNotSupported: \r\nfile: %s\r\nline: %d\r\nfunc: %s", loc.file, loc.line, loc.func);
		panic(buf);
	}
}

#endif