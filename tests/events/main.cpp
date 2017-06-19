#include <gxx/events/signal.h>
#include <gxx/debug/dprint.h>

void slt (int i) {
	dprln(i);
}

int main() {
	
	gxx::signal<int> s;
	gxx::slot<int> sslt(slt);

	s.connect(sslt);

	s.emit(67); 

}