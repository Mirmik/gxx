#include <gxx/serialize/serialize.h>
#include <gxx/debug/dprint.h>
#include <gxx/print.h>

class A : public gxx::io::printable {
public:
	int i;
	int j;
	int k;

	A(){};
	A(int i, int j, int k) : i(i), j(j), k(k) {}

	template <typename Archive>
	void reflect(Archive& a) {
		a & i;
		a & j;
		a & k;
	}

	size_t printTo(gxx::io::ostream& o) const override {
		return gxx::fprint("({}, {}, {})", i, j, k);
	}
};

int main() {
	char buf[128];

	A a(2,5,6);
	A b;

	gxx::archive::binary_writer saver{gxx::buffer(buf)};
	gxx::serialize(saver, a);

	gxx::archive::binary_reader loader{gxx::buffer(buf)};
	gxx::deserialize(loader, b);

	gxx::println(b);
}