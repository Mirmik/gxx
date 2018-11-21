#include <gxx/trent/json_settings.h>

gxx::json_settings settings("runtime.json");
gxx::settings_slice slc(settings, "mirmik");
gxx::settings_binder_numer count(slc, "count");

int main() {
	settings.sync();
	slc.sync();

	count.sync_default(0);
	count += 1.5;
	count.save();

	gxx::println(count);
}