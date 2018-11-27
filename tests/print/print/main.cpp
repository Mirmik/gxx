#include <gxx/print.h>

using namespace gxx::argument_literal;

int main() 
{
	const char * hello_str = "HelloWorld";
	char hello_arr[11] = "HelloWorld";

	dprptrln(hello_str);
	dprptrln(hello_arr);

	/*gxx::println(hello_str);
	gxx::println(hello_arr);	*/

	gxx::fprintln("{}", 33);
	gxx::fprintln("{}", hello_str);
	gxx::fprintln("{}", hello_arr);

	gxx::fprintln("{num}", "num"_a=33);
	gxx::fprintln("{str}", "str"_a=hello_str);
	gxx::fprintln("{arr}", "arr"_a=hello_arr);
}