#include <gxx/print.h> 
#include <gxx/container/hashtable.h>

class A {
public:
	hlist_node lnk;
	int key2;
};

int main() {
	gxx::println("HelloWorld");

	gxx::hashtable<int,A,&A::lnk, gxx::field<int,A,&A::key2>, gxx::hash<int>> ht;
}