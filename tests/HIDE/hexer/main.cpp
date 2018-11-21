#include <gxx/util/hexer.h>
#include <gxx/print.h>

int main(int argc, char* argv[]) {
	uint8_t buf[128];

	//const char* str = ".12.127.0.0.1:10005";
	const char* str;
	if (argc == 1) str = ".12#7F880001:10005";
	else str = argv[1];
	
	int sz;

	if ((sz = hexer(buf, 128, str, strlen(str))) < 0) {
		gxx::println("format error");
		exit(-1);
	}

	gxx::print_dump(buf, sz);
}