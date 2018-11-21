#include <gxx/print.h> 
#include <gxx/print/stdprint.h> 

#include <gxx/flow/map.h>
#include <gxx/flow/filter.h>
#include <gxx/flow/foreach.h>

#include <vector>

int main() {
	gxx::println("HelloWorld");

	std::vector<int> vec {1,2,3,4,5,6,7,8,9,10,11,33};

	//auto f = []() -> int {return 98;};

	//typename gxx::signature<decltype(f)>::return_type i;

	//std::vector<int> result = vec 
	vec
	| gxx::flow::map([] (const int& i) { return i*2;})
	| gxx::flow::filter([](const int& i){ return i >= 10 && i <= 20; })
	| gxx::flow::foreach([](const int& i){ gxx::println(i); });

	//gxx::println(vec);
}