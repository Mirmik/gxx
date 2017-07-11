#include <gxx/serialize/json.h>
#include <gxx/serialize/json_parser.h>

#include <gxx/print.h>

#include <sstream>

int main() {
	std::stringstream text(R"(
	{
		"mirmik" : 768,
		"mir" : 433,
		"kein" : ["mirmik","fasdfa"],
		"quadro" : {"i" : "a", "g" : "s"},
	}
	)"
	); 

	gxx::json js = gxx::json_parser::parse(text).unwrap();

	js.prettyPrintTo(std::cout);

	js["quadro"]["mirmik"] = 678;

	dprln(js["mir"].as_string());

	js.prettyPrintTo(std::cout);
	println();
}