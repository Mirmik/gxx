#include <gxx/debug/dprint.h>
#include <stdio.h>
#include <unistd.h>

void debug_putchar(char c) {
	int _ = write(0, &c, 1);
	(void) _;
}

void debug_write(const char* c, int i) {
	int _ = write(0, c, i);
	(void) _;
}
	
	
	