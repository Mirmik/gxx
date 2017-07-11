#include <gxx/serialize/json_settings.h>
#include <gxx/format.h>
#include <iostream>

using namespace gxx::argument_literal;

int main() {
	gxx::json_settings settings("settings.json");
	settings.load();

	int i = settings.get_number(gxx::format("{axis}/backlimit", "axis"_a = "X"), 10);
	dprln(i);

	settings.settings()["kiev"]["emo"] = 3;

	settings.save();

}