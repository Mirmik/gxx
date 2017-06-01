#include <gxx/result.h>
#include <iostream>

using namespace gxx::result;

result<int> func() {
	return gxx::result::error(5, "NotGood");
}

int main() {
	std::cout << func().unwrap() << std::endl;
}