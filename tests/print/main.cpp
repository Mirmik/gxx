#include <iostream>
#include <map>
#include <string>
#include <gxx/print.h>
#include <gxx/print/stdprint.h>


int main() {
	std::map<std::string, int> mp;

	mp.insert(std::make_pair(std::string("Hello"), 2));
	mp.insert(std::make_pair(std::string("Hello2"), 3));

	gxx::fprintln("{}", mp);
}