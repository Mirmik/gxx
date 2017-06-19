#include <gxx/bytering.h>
#include <gxx/gmsgpack/gmsg.h>

char buf[128];

int main() {
	gxx::bytering ring(buf, 128);
}