#include <gxx/debug/dprint.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __WIN32__
#   define GXX_DEBUG_STDOUT 1
#endif

#ifdef __linux__
#   define GXX_DEBUG_STDOUT 0
#endif

void debug_putchar(char c) {
    int _ = write(GXX_DEBUG_STDOUT, &c, 1);
	(void) _;
}

void debug_write(const char* c, int i) {
    int _ = write(GXX_DEBUG_STDOUT, c, i);
	(void) _;
}
	
	
	
