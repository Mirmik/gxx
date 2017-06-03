#include <gxx/getopt/cliopts.h>

int help() {
	dprln("help");
}

int main(int argc, char* argv[]) {
	gxx::cliopts opts;
	
	opts.add_integer("int", 'i', 42);
	opts.add_string("str", 's', "AllGood");
	opts.add_bool("bool", 'b', true);
	opts.add_option("help", 'h');

	if (opts.parse(1, argc, argv).is_error()) {
		help();
		return 0;
	}

	dprln(opts.get_integer("int").unwrap());
	dprln(opts.get_string("str").unwrap());
	dprln(opts.get_bool("bool").unwrap());
	
	if (opts.get_option("help").unwrap()) {
		help();
		return 0;
	}
}