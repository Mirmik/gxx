#include <gxx/util/macro.h>
#include <gxx/debug/dprint.h>

int sum(int a, int b) {
	DTRACE_ARGS(a, b);
}

int main(int argc, const char ** argv) 
{	
	DTRACE_ARGS(argc);

	sum(3, 5);

	dprln("mirmik", "was", "here", 1111);
}