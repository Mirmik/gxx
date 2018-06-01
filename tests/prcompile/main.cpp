#include <gxx/chain.h>
#include <gxx/print.h>

#include <array>

void* print_integer_argument(void* argptr, int8_t* sts) {
	gxx::println("print_integer_argument", *(int*)argptr);
	return (char*)argptr + sizeof(int);
}

int main() {
	std::array<gxx::chainfunc_t, 2> funcs {print_integer_argument, print_integer_argument };
	std::array<int, 2> args {3, 4};

	gxx::chain ch(gxx::make_objbuf(funcs), gxx::make_buffer(args));
	ch.exec();
}
