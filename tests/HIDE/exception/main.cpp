#include <gxx/exception.h>

using namespace gxx::argument_literal;

int main() {
	throw GXX_NOT_SUPPORTED;

	location loc = current_location();
	gxx::fprintln("{file}", "file"_a = loc.file);

}