#include <gxx/trace.h>

int foo(int a) 
{
	TRACE_ARGS(a);	
}

int main() {
	TRACE();

	foo(78);
}