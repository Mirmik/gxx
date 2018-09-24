#ifndef GXX_PANIC_H
#define GXX_PANIC_H

#include <gxx/util/location.h>

#ifdef __cplusplus
#include <cstring>
#include <cstdio>
#endif

__BEGIN_DECLS

void panic(const char* str);

__END_DECLS

#define PANIC_TRACED()							\
{												\
	debug_print_location(current_location());	\
	panic("TRACED");							\
}

#ifdef __cplusplus
namespace gxx {
	using ::panic;
}
#endif

#endif
