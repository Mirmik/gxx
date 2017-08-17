#include <gxx/serialize/json_settings.h>
#include <gxx/format.h>
#include <iostream>

using namespace gxx::argument_literal;

int main() {
	gxx::json_settings settings("settings.json");
	settings.load();

//	int i = settings.settings().get_num(gxx::format("{axis}/backlimit", "axis"_a = "X"), 10);
	// i = settings.get_array(gxx::format("{axis}/backlimit", "axis"_a = "X"));
//	dprln(i);

	settings.settings()["kiev"]["emo"] = 3;

	settings.save();

}