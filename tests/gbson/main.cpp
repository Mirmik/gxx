#include <gxx/trent/gbson.h>

int main() {
	gxx::trent tr;

	tr["a"] = 4;
	tr["b"] = std::string("mir");
	tr["c"][0] = 25.33;
	tr["c"][1] = std::string("HelloWorld");

	char buf[128];

	int ret = gxx::gbson::dump(tr, buf, 128);
	gxx::println("ret: ", ret);

	if (ret < 0) {
		gxx::println("error in gbson dump");
		exit(-1);
	}

	gxx::print_dump((const void*)buf, ret);

	ret = gxx::gbson::load(tr, buf, ret);
	if (ret < 0) {
		gxx::println("error in gbson load");
		exit(-1);
	}

	gxx::println(ret);
	gxx::println(tr);

}
