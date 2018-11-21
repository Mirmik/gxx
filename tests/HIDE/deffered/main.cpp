#include <gxx/event/deffered.h>
#include <gxx/print.h>

void hello(int a, int b) {
	gxx::vprintln("hello", a, b);
}

int main() {
	auto pend = gxx::make_vdeffered(hello, 67, 89);

	pend.invoke();
}