#ifndef GXX_INET_TCP_SERVER_H
#define GXX_INET_TCP_SERVER_H

#include <gxx/inet/socket2.h>

namespace gxx {
	namespace inet {
		struct tcp_server : public inet::socket {
			tcp_server() : socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) {}
			tcp_server(gxx::inet::hostaddr addr, int port) : tcp_server() {
				bind(addr, port);
			} 
		};
	}
}

#endif