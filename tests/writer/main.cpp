#include <gxx/io2/format_writer.h>

gxx::io::debug_strmout debug;

int main() { 
	debug.println("HelloWorld");

	gxx::io::format_writer w(debug);

//	w.write_int(32, gxx::IntegerSpec().prefix(gxx::Prefix::Hex));
}