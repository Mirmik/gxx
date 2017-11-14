#include <gxx/result.h>
#include <gxx/print.h>

using namespace gxx::result_type;

result<int> func() {
	return 3;
	return error("AllBad");
}

int main() {
	gxx::println(func().unwrap());
}