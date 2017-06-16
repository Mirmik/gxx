#include <gxx/debug/dprint.h>
#include <gxx/gmsgpack/gmsgpack.h>


int main() {
	char gmsgbuf[128];
	gmsg_t gmsg;

	gmsg_init(&gmsg, gmsgbuf, 128);

	gmsg_start(&gmsg);
	gmsg_add_part(&gmsg, "HelloWorld", 10);
	gmsg_finish(&gmsg);


	dpr_dump(gmsg.buf, gmsg.ptr - gmsg.buf);
}