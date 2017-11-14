#include <iostream>
#include <gxx/container.h>
#include <gxx/generator.h>
#include <gxx/print.h>
#include <gxx/util/iteration_counter.h>

using namespace gxx::gen;

int main() {
	gxx::println("HelloWorld");

	std::vector<int> vec {3,4,5};

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

	dprln("TODO");

	//Двойной фильтр подыхает до использования.
	//Решить перемещением временного объекта.
}