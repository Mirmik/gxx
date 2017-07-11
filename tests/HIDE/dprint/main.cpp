#include <gxx/debug/dprint.h>
#include <gxx/format.h>

int main() {
	dprln("HelloWorld");
	dpr_dump("HelloWorld", 10);

	dprf("Hello {}", "World");
}