#include <gxx/debug/dprint.h>
#include <gxx/gmsgpack/gmsg.h>
#include <gxx/io/strm.h>

gxx::io::debug_strmout dout;

int main() {
	gxx::gmessage_writer gmsg(dout);

	dout.println("Hello {}!", "World");
}