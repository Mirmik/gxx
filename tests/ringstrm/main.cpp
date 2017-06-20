#include <gxx/io2/ringstrm.h>

char buf[128];
gxx::io::ringstrm ring { gxx::buffer(buf) };

char buf2[128];

int main() {
	ring.println("Hello {}!", "World");
	
	int ret = ring.read(buf, 128);
	debug_write(buf, ret);
}