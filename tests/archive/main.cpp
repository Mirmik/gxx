#include <gxx/transport/serialize.h>
#include <gxx/debug/dprint.h>

class A {
public:
	int i = 3;
	int j = 1;
	int k = 2;

	template <typename Archive>
	void serialize(Archive& a) {
		a & i;
		a & j;
		a & k;
	}
};

int main() {
	char buf[128];

	A a;
	A bb;

	gxx::serialize::binary_saver saver{gxx::buffer(buf)};
	saver.dump(a);

	gxx::buffer b = saver.getbuf();
	dpr_dump(b.data(), b.size());

	gxx::serialize::binary_loader loader(b);
	loader.load(bb);
}