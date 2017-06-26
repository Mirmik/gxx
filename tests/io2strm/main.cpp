#include <gxx/io/strm.h>
#include <gxx/gmsgpack/gmsg.h>

gxx::io::debug_strmout dstrm;
gxx::gmessage_writer wmsg(dstrm);

int main() {
	dstrm.dumpmode(true);

	wmsg.prefix();
	wmsg.part("Hello\xDBWorld", 11);
	wmsg.postfix();
}