#include <gxx/gstuff/sender.h>
#include <gxx/gstuff/automate.h>

#include <gxx/io/ringbuffer.h>
#include <gxx/debug/debug_ostream.h>

void dumper(gxx::buffer buf) {
	dprln("dumper:", buf);
}

int main() {
	char ring[128];
	gxx::io::ringbuffer buf(ring);

	char _pack[128];
	gxx::gstuff::automate pack(_pack);
	gxx::gstuff::sender opack(buf);

	pack.set_callback(dumper);

	opack.start_message();
	opack.print("Hello");
	opack.putchar(gxx::gmsg::strt);
	opack.print("World");
	opack.end_message();

	gxx::debug_ostream dout;
	
	while(buf.avail()) {
		char c = buf.getchar();
		pack.newchar(c);
	}
}