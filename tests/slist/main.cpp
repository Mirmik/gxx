#include <gxx/slist.h>
#include <gxx/debug/dprint.h>

struct A {
	slist_head lnk;
	int i;
	A(int i) : i(i) {}
};

gxx::slist<A, &A::lnk> sl;

int main() {
	A a(21);
	A b(33);
	A c(43);

	sl.move_front(a);
	sl.move_front(b);
	sl.move_front(c);

	for(auto& s : sl) dprln(s.i);
}