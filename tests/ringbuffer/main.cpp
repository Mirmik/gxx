#include <gxx/io/ringbuffer.h>
#include <gxx/debug/dprint.h>
#include <gxx/debug/debug_ostream.h>

gxx::io::ringbuffer* rng;

void func() {
	dprln(rng->avail());
	rng->retrans(gxx::debug_ostream());
}

int main() {
	gxx::io::ringbuffer ring(gxx::allocate_buffer(128));
	rng =&ring;

	ring.avail_callback(func);
	ring.fmtln("AllBad");
	dprln(rng->avail());
}