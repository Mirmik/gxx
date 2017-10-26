#include <iostream>
#include <gxx/container.h>
#include <gxx/generator.h>
#include <gxx/print.h>

#include <gxx/util/iteration_counter.h>

using namespace gxx::gen;

#define do_after_iteration(b) static int _concate(__internal_var, __LINE__) = 0; \
        if (_concate(__internal_var, __LINE__) < b) ++_concate(__internal_var, __LINE__); else

int main() {
	gxx::println("HelloWorld");

	std::vector<int> vec {3,4,5};
	/*for (auto r : mapping(vec, [](int i){ return i * 2; })) {
		std::cout << r << std::endl;
	}*/

	for (auto r : 
		filter(
			mapping(vec, [](int i) { 
				gxx::fprintln("mapping {}", i);
				return i * 2; 
			}), 
			[](int i) { 
				gxx::fprintln("filter {}", i);
				return i != 5; 
			})) 
	{
		
		std::cout << r << std::endl;
		do_after_iteration(7) exit(0);
	}
}