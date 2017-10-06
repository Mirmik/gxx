#include <gxx/serialize/json.h>
#include <gxx/serialize/json_settings.h>

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

	if (settings.settings().is_nil()) {
		settings.settings()["summer"] = "winter";
		settings.save();
	}

	gxx::trent t = settings.settings();

	gxx::json::pretty_print_to(t, std::cout);
	gxx::json::pretty_print_to(settings.settings(), std::cout);
}