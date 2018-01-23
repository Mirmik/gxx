#include <gxx/trent/json.h>
#include <gxx/trent/json_settings.h>

#include <sstream>
#include <iostream>

int main() {
	std::stringstream text(R"(
	{
		"mirmik" : 768,
		"mir" : -12222222222222222222222222.000,
		"kein" : ["mirmik","fasdfa"],
		"quadro" : {"i" : "a", "g" : "s"},
	}
	)"
	); 

	gxx::trent js = gxx::json::parse(text).unwrap();
	gxx::json::pretty_print_to(js, std::cout);

	js["quadro"][6][1] = 678;
	gxx::json::pretty_print_to(js, std::cout);

	gxx::json_settings settings("settings.json");
	settings.load();

	if (settings.root().is_nil()) {
		settings["summer"] = std::string("winter");
		settings.save();
	}

	gxx::trent t = settings.root();

	gxx::json::pretty_print_to(t, std::cout);
	gxx::json::pretty_print_to(settings.root(), std::cout);
}