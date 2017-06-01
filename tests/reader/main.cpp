#include <gxx/reader.h>

int main() {
	gxx::debug_writer writer;

	writer.write("HelloWorld", 11);
	writer.write_fill('t', 32);
	writer.putchar('\n');

	writer.write_int(38, gxx::IntegerSpec().prefix(gxx::Prefix::Hex));
}