#include <gxx/serialize/json_settings.h>
#include <fcntl.h>

int main() {
	gxx::json_settings settings("settings.json");

	settings.load();
}