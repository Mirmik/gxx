#include <gxx/serialize/json_settings.h>
#include <fcntl.h>

int main() {
	gxx::json_settings settings("settings.json");

	//gxx::tree(gxx::tree_type::dictionary);

	gxx::datatree tr;
	//tr["lala"][3] = 713

	//auto& dflt = settings.default_settings();

	//dflt["A"][0] = 37;
	//dflt["A"][1] = "Mirmik";

	settings.load();

	//settings["A"] = 329;
	//settings["mir222mik"] = 3231239;
	//settings["quadro"]["mirm"] = 785;

	settings.get_number("mirmik/harad/kil", 87);

	settings.save();

}