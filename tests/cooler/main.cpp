#include <gxx/container.h>
#include <gxx/print.h>
#include <gxx/util/iteration_counter.h>

int main() {
	for (auto i : 
		gxx::gen::filter([](auto i) { return i % 2 == 0; },
			gxx::gen::filter([](auto i) { return i % 3 == 0; },
				gxx::gen::range(0,30)
			)
		)) 
	{
		gxx::println(i);
		do_after_iteration(10) exit(0);
	}

	/*for (auto i : 
		gxx::gen::filter([](auto i) { return i % 3 == 0; },
			gxx::gen::range(0,30)
		)
	) {
		gxx::println(i);
	}*/
}