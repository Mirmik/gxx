#include <iostream>
#include <gxx/dlist.h>

class A {
public:
	dlist_head link;
};

int main() {
	gxx::dlist<A, &A::link> list;	
}