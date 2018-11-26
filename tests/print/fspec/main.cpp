#include <gxx/print.h>

int main() 
{
	gxx::fprintln("\t{:10>U} {:10>} {:10>} {:10>}", "", "num", "case", "arg");
	gxx::fprintln("\t{:10>U} {:10>} {:10>} {:10>}", "maks", 10, 20, 30);
	gxx::fprintln("\t{:10>U} {:10>} {:10>} {:10>}", "frank", 10, 20, 30);
	gxx::fprintln("\t{:10>U} {:10>} {:10>} {:10>}", "trisha", 10, 20, 30);
}