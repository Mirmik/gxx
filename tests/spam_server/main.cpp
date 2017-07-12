#include <thread>
#include <chrono>
#include <iostream>

#include <gxx/inet/spam_server.h>

int main() {
	gxx::spam_server srv(9996);
	if (srv.start() < 0) {
		dprln(srv.error());
	}

	while(true) {
		srv.print("{0}", "Mirmik");
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}