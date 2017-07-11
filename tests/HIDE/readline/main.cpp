#include <gxx/simple_readline.h>
#include <gxx/debug/dprint.h>

void line_handler(const char* str, size_t sz) {
	dprln("line_handler");
	dprln(str);
} 

int full_handler(gxx::simple_readline& rl) {
	return -1;
} 

int main() {
	char buf[16];
	gxx::simple_readline rl(gxx::buffer(buf,8));
	rl.set_line_handler(line_handler);
	rl.set_full_handler(full_handler);

	rl.write("HelloWorld\nHelloWorld\nHelloWorld\n", 30);

	dprln(rl.line());
}