#include <gxx/debug/dprint.h>

int main(int argc, const char ** argv) {
	const char * hello = "HelloWorldHelloWorldHelloWorld";
	char* hello_ = (char*) hello;

	bool bool_var = true;
	const uint8_t a = 1;
	const int16_t b = 2;
	const uint32_t c = 3;
	const volatile int64_t d = 4;
	const volatile double f = 0.567;

	DTRACE();

	dprln(hello);
	dprln(hello_);

	dprln(a); 
	dprln(b); 
	dprln(c); 
	dprln(d);

	DPRINT(a); 
	DPRINT(b); 
	DPRINT(c); 
	DPRINT(d);
	
	dprln(0.126); 
	dprln(bool_var);

	DPRINT(0.126); 
	DPRINT(bool_var);

	debug_print_dump(hello, 30);
}