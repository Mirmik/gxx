#include <iostream>
#include <gxx/vector.h>

int main() {
	gxx::vector<int> vecint;

	vecint.push_back(56);
	vecint.insert(0, 53);

	for(auto& val : vecint) {
		std::cout << val << std::endl;
	}

	auto vec2 = vecint;

	for(auto& val : vec2) {
		std::cout << val << std::endl;
	}
}