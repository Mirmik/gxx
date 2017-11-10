#include <gxx/packager/packager.h>
#include <gxx/packager/opackager.h>
#include <gxx/io/ringbuffer.h>
#include <gxx/debug/debug_ostream.h>

void dumper(gxx::buffer buf) {
	dprln(buf);
}

int main() {
	char ring[128];
	gxx::io::ringbuffer buf(ring);

	char _pack[128];
	gxx::packager pack(_pack);
	gxx::opackager opack(buf);

	pack.set_callback(dumper);

	opack.prefix();
	opack.part("Hello");
	opack.part(gxx::gmsg::strt);
	opack.part("World");
	opack.postfix();

	gxx::debug_ostream dout;
	
	while(buf.avail()) {
		char c = buf.getchar();
		pack.newchar(c);
	}
}