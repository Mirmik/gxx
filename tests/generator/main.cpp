#include <iostream>
#include <gxx/generator.h>

class range : public gxx::generator<int, range> {
	int start;
	int stop;

public:
	range(int start, int stop) : start(start), stop(stop) {}

	bool next() {
		start++;
		if (start == stop) return false;
		return true;
	}

	int value() {
		return start;
	}
};

int main() {
	for ( auto r: range(3,10) ) {
		std::cout << r << std::endl;
	}
}