#include <gxx/hashtable.h>

class A {
public:
	int key;	
	hlist_node hlnk;

	static int& getkey(A& a) { return a.key; }
};

int main() {
	gxx::static_hashtable<10, A, int, &A::hlnk> htable;

	A a;
	a.key = 5;

	htable.put(a);

	dprln(htable.get(5)->key);
}