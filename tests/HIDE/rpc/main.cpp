#include <gxx/rpc/bincall.h>

gxx::rpc::rpcresult<int> add(int a, int b) {
	return gxx::rpc::status::OK;
	return a + b;
}

gxx::rpc::rpcresult<std::string> sub(int a, int b) {
	return std::string("Hello");
}

int main() {
	auto addcall = gxx::rpc::make_bincall(gxx::make_delegate(add));
	auto subcall = gxx::rpc::make_bincall(gxx::make_delegate(sub));

	char dump[128];
	gxx::archive::binary_writer archive(dump);
	
	int a = 1;
	int b = 1;

	gxx::serialize(archive, a);
	gxx::serialize(archive, b);

	char ans[128];

	gxx::archive::binary_reader reader(gxx::buffer(dump, archive.length()));
	gxx::archive::binary_writer writer(ans);
	
	gxx::rpc::status sts = subcall.invoke(reader, writer);
	gxx::println(sts);

	debug_print_dump(ans, writer.length());
}