#include <iostream>
#include <gxx/inet/socket.h>

#include <gxx/format.h>

int main() {
	gxx::socket sock(gxx::hostaddr("127.0.0.1"), 6777);	

	dprhexln(sock.host().addr);
	dprln(sock.port());

	sock.open();
	if (sock.connect()) {
		dprln("error: {}", sock.error());
	}


}