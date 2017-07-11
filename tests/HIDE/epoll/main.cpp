#include <gxx/format.h>
#include <gxx/linux/epoll.h>
#include <gxx/inet/socket.h>

int main() {
	dprln("Hello, {:U}!", "world");

	gxx::epoll epl;
	epl.create();

	gxx::socket sock(gxx::SocketType::Tcp, "127.0.0.1", 7777);
	sock.connect();

	epl.add(sock.fd());

	while(true) {
		struct epoll_event event = epl.wait();

		if (event.events & EPOLLIN) {
			dprln("EPOLLIN");
			char buf[128];
			int ret = sock.read(buf, 128);
			dprln(ret);
		}

		if (event.events & EPOLLOUT) {
			dprln("EPOLLOUT");
		}

		if (event.events & EPOLLERR) {
			dprln("EPOLLERR");
		}

		if (event.events & EPOLLHUP) {
			dprln("EPOLLHUP");
		}

	}
}