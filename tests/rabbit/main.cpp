#include <gxx/print.h>
#include <gxx/io/std.h>
#include <gxx/rabbit/topo2.h>

int main() {
	//gxx::println("HelloWorld");

	rabbit::point pnts[3] = {
		{0,0},
		{0,1},
		{1,0}
	};

	rabbit::loop2 lp {
		rabbit::line2(pnts[0], pnts[1]),
		rabbit::line2(pnts[1], pnts[2]),
		rabbit::line2(pnts[2], pnts[0])
	};

	//gxx::println(lp.check_closed());
	//gxx::fprintln("m{}ir", "mik");
}