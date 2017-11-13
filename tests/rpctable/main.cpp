#include <gxx/rpc/bincall.h>
#include <gxx/rpc/bincalltable.h>
#include <gxx/cstring.h>

gxx::rpc::rpcresult<int> add(int a, int b) {
	dprln("add");
	dprln("a", a);
	dprln("b", b);
	return a + b;
}

gxx::rpc::rpcresult<int> sub(int a, int b) {
	dprln("sub");
	dprln("a", a);
	dprln("b", b);
	return a - b;
}
 
int main(int argc, char* argv[]) {
	gxx::rpc::bincalltable<gxx::cstring, 32> bintable;
	bintable.add("add", gxx::make_delegate(add));
	bintable.add("sub", gxx::make_delegate(sub));
	auto call = bintable.find(argv[1]);
	if (call == nullptr) {
		dprln("WrongFunction");
		return 0;
	}

	char dump[128];
	gxx::archive::binary_writer archive(dump);
	
	for (int i = 2; i < argc; ++i) {
		gxx::serialize(archive, atoi(argv[i]));
	}	

	char ans[128];

	gxx::archive::binary_reader reader(gxx::buffer(dump, archive.length()));
	gxx::archive::binary_writer writer(ans);
	
	gxx::rpc::status sts = call->invoke(reader, writer);
	gxx::println(sts);

	debug_print_dump(ans, writer.length());
}