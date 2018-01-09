#include <gxx/ring.h>
#include <gxx/debug/dprint.h>

int main() {
	gxx::ring<int> r(15);

	r.push(33);
	r.push(32);
	r.push(31);
	//int ret = r.pop();

	dprln(r.front()); r.pop();
	dprln(r.front()); r.pop();
	dprln(r.front()); r.pop();
}