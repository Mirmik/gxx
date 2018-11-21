#include <iostream>
#include <string>
#include <thread>
#include <gxx/sshell.h>
#include <gxx/debug/dprint.h>

int hello(int argc, char**) {
	dprln("HelloWorld");
}

sshell_command cmd[] = {
	{ "hello", hello }
};

void read_func() {
	while(1) {
		int sts;
		std::string str;
		std::getline(std::cin, str);

		sshell_execute_safe(str.c_str(), cmd, sizeof(cmd)/sizeof(sshell_command), &sts);
		//shell.execute(str, &sts);
		//if (sts != 0) {
		//	dprln(sshell_strerr(sts));
		//}
	}
}

int main() {
	read_func();
}