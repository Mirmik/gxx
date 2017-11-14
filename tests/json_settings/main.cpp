#include <gxx/serialize/json_settings.h>
#include <gxx/print.h>
#include <iostream>

using namespace gxx::argument_literal;

int main() {
	gxx::json_settings settings("settings.json");
	settings.load();

	gxx::println(settings.settings()["kiev"]["emo"]);

	settings.settings()["kiev"]["emo"] = 4;
	settings.save();

}