#ifndef GXX_PANIC_H
#define GXX_PANIC_H

#ifdef __cplusplus
#include <gxx/util/location.h>
#include <cstring>
#include <cstdio>
#endif

__BEGIN_DECLS

void panic(const char* str);

__END_DECLS

#define PANIC_TRACED(...)					\
{debug_print_location(current_location());	\
gxx::panic(__VA_ARGS__);}

#ifdef __cplusplus
namespace gxx {
	using ::panic;
}
#endif

#endif
