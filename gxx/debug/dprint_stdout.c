#include <gxx/debug/dprint.h>
#include <stdio.h>
#include <unistd.h>

int debug_putchar(char c) {
	return write(0, &c, 1);
}

int debug_write(const char* c, int i) {
	return write(0, c, i);
}
	
	
	