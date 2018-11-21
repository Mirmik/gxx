#include <gxx/print.h>
#include <gxx/util/access.h>

int main() {

	uint32_t a = 28;

	//UINT32_LHI(a) = 1;

	char buf[512];
	uint32_to_hex(buf, a);
	(buf, a);

	gxx::writeln(buf, 8);

}