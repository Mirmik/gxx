#include <gxx/serialize/json.h>
#include <gxx/serialize/json_settings.h>

#include <sstream>
#include <iostream>

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

	js["quadro"][6][1] = 678;
	js.printTo(std::cout);

	gxx::json_settings settings("settings.json");
	settings.load();

	if (settings.settings().is_nil()) {
		settings.settings()["summer"] = "winter";
		settings.save();
	}

	settings.settings().printTo(std::cout);
}