#include <gxx/print.h>
#include <gxx/trent/binder.h>
#include <gxx/trent/settings.h>
#include <gxx/trent/json_settings.h>

int main() {

	gxx::json_syncer syncer("settings.json");
	gxx::trent_binder<int32_t, gxx::trent_syncer_slice> ibind(syncer, "mirmik/jjj");

	gxx::println(ibind.get());
	ibind.update(25);
}