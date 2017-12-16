#include <gxx/container.h>
#include <gxx/print.h>
#include <gxx/util/iteration_counter.h>

int main() {
	for (auto i : 
		gxx::gen::mapping([](auto i) { return i * 3; },
			gxx::gen::filter([](auto i) { return i % 3 == 0; },
				gxx::gen::range(0,30)
			)
		)) 
	{
		gxx::println(i);
	}
}