#include <gxx/debug/dprint.h>
#include <stdio.h>
#include <unistd.h>

void debug_putchar(char c) {
	int ret = write(0, &c, 1);
}

void debug_write(const void* c, int i) {
	int ret = write(0, c, i);
}
	
	
	