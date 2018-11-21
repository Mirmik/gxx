#include <gxx/math/fixed.h>

int main() {
	fxuint32_t a(3.31);
	fxuint32_t b(16.1);

	gxx::println(a);
	gxx::println(b);
	gxx::println(a*b);
}