#include <gxx/io2/format_writer.h>

gxx::io::debug_strmout debug;

int main() { 
	//debug.println("HelloWorld");

	gxx::io::format_stream_writer w(debug);
	w.println("HelloWorld");
	w.println("Hello {}!", "World");

	gxx::string str;
	gxx::io::format_string_writer w2(str);

	w2.println("Hello {}!", "World");

	dpr(str.c_str());


//	w.write_int(32, gxx::IntegerSpec().prefix(gxx::Prefix::Hex));
}