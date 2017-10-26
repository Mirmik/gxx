#include <iostream>
#include <gxx/inet/socket.h>

#include <gxx/print.h>

#include <thread>

#include <gxx/inet/server.h>

void func() {
	gxx::socket sock(gxx::socket::type::Tcp, gxx::hostaddr("127.0.0.1"), 6700);
	if (!sock.is_connected()) {
		dprln("error1: {}", sock.error());
	}

	char buf[128];
	int ret = sock.read(buf, 128);
	dprln("finish read");
	dprln("ret = {}", ret);

	if (ret < 0) {
		exit(-1);
	}

	debug_write(buf, ret);

	sock.close();
} 

int main() {
	gxx::server serv(gxx::socket::type::Tcp, 6700);
	if (!serv.is_listening()) {
		dprln("error2: {}", serv.error());
	}

	std::thread thr(func);

	gxx::socket client = serv.accept();
	//dprln("client");

	client.print("i send to you");

	thr.join();

	serv.close();
}