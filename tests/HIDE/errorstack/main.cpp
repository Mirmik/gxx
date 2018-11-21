#include <thread>
#include <chrono>
#include <iostream>

#include <gxx/logger/logger.h>
#include <gxx/logger/targets/stack.h>

gxx::log::stack errstack;
gxx::log::logger logger("Errors");

int main() {
	logger.link(errstack);

	logger.warn("Overvoltage");
	logger.error("Overvoltage");
	logger.error("ThermalOverflow");

	for(auto& s : errstack.list()) {
		dprln(s);
	}
}