#include <gxx/events/signal.h>
#include <gxx/debug/dprint.h>

void slt () {
	dprln("Hello");
}

int main() {
	
	gxx::sigflag s;
	gxx::slot<> sslt(slt);
	sslt.unconnect_on_invoke(true);

	s.connect(sslt);

	s.sigon(); 
	s.connect(sslt);

	s.sigoff();
	s.connect(sslt);
}