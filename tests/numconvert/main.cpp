#include <gxx/util/numconvert.h>
#include <iostream>

int main() {
	char* end;
	std::cout << atod("-33.687", &end) << std::endl;
}