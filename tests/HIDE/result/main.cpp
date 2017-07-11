#include <gxx/result.h>
#include <iostream>

using namespace gxx::result_type;

int i = 4;

result<int> int_val() {
	return 3;
}

result<int&> int_ref() {
	return i;
}

result<int&&> int_rref() {
	return std::move(i);
}

int main() {
	dprln(int_val().unwrap());
	dprln(int_ref().unwrap());
	dprln(int_rref().unwrap());
}