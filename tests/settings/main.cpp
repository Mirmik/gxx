#include <gxx/print.h>
#include <gxx/trent/settings.h>
#include <gxx/trent/json_settings.h>

int main() {
	gxx::json_settings jssts("mirmik.json");
	jssts.sync();

	gxx::println(jssts.node());
	gxx::println(jssts.node()["mirmik2"]);
	gxx::println(jssts.node()["mirmik2"][1]);

	gxx::trent_settings_slice slice(jssts, "mirmik2/1/mir");

	slice.sync();
	gxx::println(slice.node());
}