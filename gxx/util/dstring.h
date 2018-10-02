#ifndef GXX_UTIL_DSTRING_H
#define GXX_UTIL_DSTRING_H

#include <stdlib.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

int bytes_to_dstring(char* out, const void* data, size_t size);

__END_DECLS

#endif