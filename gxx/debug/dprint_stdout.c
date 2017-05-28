#include <gxx/debug/dprint.h>
#include <stdio.h>
#include <unistd.h>

void debug_putchar(char c) {
	putchar(c);
}

void debug_write(const void* c, int i) {
	int ret = write(0, c, i);
}
	
	
	