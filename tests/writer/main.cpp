#include <gxx/io/iostream.h>
#include <gxx/io/writer.h>

int main() {
	gxx::debug_ostream debug; 
	debug.write("HelloWorld", 10);

	gxx::text_writer w(debug);

	w.write_int(32, gxx::IntegerSpec().prefix(gxx::Prefix::Hex));

}