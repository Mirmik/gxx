#include <gxx/print.h>
#include <gxx/util/hash.h>

int main() {
	auto ret = gxx::sdbm_hash("HelloWorld");
	debug_printhex_uint32(ret);
	//gxx::print_dump(&ret, sizeof(ret));
}