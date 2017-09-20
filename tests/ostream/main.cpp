//#include <gxx/arglist2.h>
#include <gxx/io/fstream.h>
#include <gxx/io/printable.h>

using namespace gxx::argument_literal;

class A : public gxx::io::printable{
public:	
	int i = 8;
	size_t printTo(gxx::io::ostream& o) const override {
		o.print("A");
		o.print(i);
	}
};

int main() {
	int i = 33;
	const char* str = "world";

	gxx::io::fstream cout(1);
	
	cout.fmtln("hello {}", "world");
	cout.fmtln("hello {}", str);
	cout.fmtln("hello {w}", "w"_a = "world");
	cout.fmtln("hello {w}", "w"_a = str);

	cout.fmtln("hello {:>10}{:10>}", 332, "world");
	cout.fmtln("hello {}", i);
	cout.fmtln("hello {w}", "w"_a = 32);
	cout.fmtln("hello {w}", "w"_a = i);

	cout.fmtln("hello {1}, {0}", 'a', "b");
}