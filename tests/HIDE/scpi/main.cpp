#include <gxx/serialize/scpi.h>
#include <gxx/print.h>

std::string scpistr = R"(AXIS0:HEAD:TEMP2:MIRmik 32.33, 32.11, "mjkj dfasdf?"  ?)";

int main() {
	gxx::scpi_string_parser strparser(scpistr);

	if (strparser.is_error) return 0;

	for (auto& v : strparser.headers) {
		gxx::fprintln("{}, {}", v.str.c_str(), v.num);
	}

	for (auto& v : strparser.arguments) {
		gxx::fprintln("{}", v.c_str());
	}

	dprln("question:", strparser.is_question);
}