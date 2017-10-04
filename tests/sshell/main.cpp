#include <iostream>
#include <string>
#include <thread>
#include <gxx/sshell.h>
#include <gxx/debug/dprint.h>

int hello_world() {
	dprln("HelloWorld");
}

gxx::sshell shell;

void read_func() {
	while(1) {
		int sts;
		std::string str;
		std::getline(std::cin, str);
		shell.execute(str, &sts);
		if (sts != 0) {
			dprln(shell.strerr(sts));
		}
	}
}

int main() {
	shell.add("hello", hello_world);
	read_func();
}