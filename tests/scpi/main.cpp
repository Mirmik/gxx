#include <gxx/serialize/scpi.h>
#include <gxx/format.h>

std::string scpistr = "AXIS0:HEAD:TEMP2:MIRmik 32, Dfgrt ";

int main() {
	gxx::scpi_string_parser strparser(scpistr);

	if (strparser.is_error) return 0;

	for (auto& v : strparser.headers) {
		gxx::fmt::println("{}, {}", v.str.c_str(), v.num);
	}

	for (auto& v : strparser.arguments) {
		gxx::fmt::println("{}", v.c_str());
	}

	dprln(strparser.is_question);
}