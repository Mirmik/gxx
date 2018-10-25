#include <gxx/debug/dprint.h>

int main() {
	const char * hello = "HelloWorldHelloWorldHelloWorld";
	char* hello_ = (char*) hello;

	debug_print_dump(hello, 30);

	bool bb = true;
	const uint8_t a = 1;
	const uint16_t b = 1;
	const uint32_t c = 1;
	const volatile uint64_t d = 1;
	const volatile double f = 0.126;

	dpr(hello); dln();
	dpr(hello_); dln();
	dpr(a); dpr(b); dpr(c); dpr(d);
	dprln(0.126); 
	dprln(bb);
}