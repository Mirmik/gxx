#include <gxx/rpc/invoker.h>
#include <gxx/print.h>

#include <gxx/serialize/serialize.h>

template<typename Ret, typename ... Args>
using bininvoker = gxx::rpc::invoker<gxx::archive::binary_string_reader, gxx::archive::binary_string_writer, gxx::rpc::result<Ret>, Args ...>;

gxx::rpc::result<int> hello(int a, int b) {
	gxx::println(a, b);
	return 3;
}

bininvoker<int, int, int> inv(hello);

int main() {
	std::string rstr;
	std::string wstr;

	gxx::archive::binary_string_writer wpre(rstr);

	int a = 88;
	int b = 77;

	gxx::serialize(wpre, a);
	gxx::serialize(wpre, b);

	gxx::println(rstr.size());

	gxx::archive::binary_string_reader r(rstr);
	gxx::archive::binary_string_writer w(wstr);

	inv.invoke(r, w);

	gxx::println(wstr.size());	
}