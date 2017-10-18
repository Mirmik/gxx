#include <gxx/debug/dprint.h>

void abort(void) {
	debug_print("abort");
	while(1);
	//panic("Aborted");
}
