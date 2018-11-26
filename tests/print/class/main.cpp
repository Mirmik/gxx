#include <gxx/print.h>

class A {
public:
	/*ssize_t printTo(gxx::io::ostream& o) const {
		return o.print("A");
	}*/
};

std::ostream& operator << (std::ostream& o, const A& ref) {
	o << "A";
	return o;
}

int main() 
{
	gxx::println(A());
}