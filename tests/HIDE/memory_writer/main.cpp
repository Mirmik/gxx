#include <iostream>
#include <gxx/memory_writer.h>

int main() {
	uint width = 21;

	char buffer[256];
	gxx::memory_writer w(buffer, 256);

	w.write_cstr("Right", gxx::CharStrSpec()
		.align(gxx::Alignment::Right)
		.width(width));

	w.putchar('\n');

	w.write_cstr("Left", gxx::CharStrSpec()
		.align(gxx::Alignment::Left)
		.width(width));

	w.putchar('\n');

	w.write_cstr("Center", gxx::CharStrSpec()
		.align(gxx::Alignment::Center)
		.width(width));

	w.putchar('\n');

	w.write_cstr("Right", gxx::CharStrSpec()
		.align(gxx::Alignment::Right)
		.width(width)
		.charCase(gxx::CharCase::Upper));

	w.putchar('\n');

	w.write_cstr("Left", gxx::CharStrSpec()
		.align(gxx::Alignment::Left)
		.width(width)
		.charCase(gxx::CharCase::Upper));

	w.putchar('\n');

	w.write_cstr("Center", gxx::CharStrSpec()
		.align(gxx::Alignment::Center)
		.width(width)
		.charCase(gxx::CharCase::Upper));

	w.putchar('\n');
	w.write_cstr("Numbers:");
	
	w.putchar('\n');
	w.write_int(42);	
	
	w.putchar('\n');
	w.write_int(42, gxx::IntegerSpec()
		.align(gxx::Alignment::Center)
		.width(width)
		.base(16));	

	w.putchar('\n');
	w.write_int(42, gxx::IntegerSpec()
		.align(gxx::Alignment::Left)
		.width(width)
		.base(8)
		.prefix(gxx::Prefix::Oct));	

	w.putchar('\0');

	std::cout << buffer << std::endl;
}