#ifndef GXX_INET_TCP_SERVER_H
#define GXX_INET_TCP_SERVER_H

#include <gxx/inet/tcp_socket.h>

namespace gxx {
	namespace inet {
		struct tcp_server : public inet::socket {
			tcp_server() = default;
			
			tcp_server(int port) : tcp_server() {
				init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				bind("0.0.0.0", port);
				inet::socket::listen(10);
			} 
			
			tcp_server(gxx::inet::hostaddr addr, int port) : tcp_server() {
				init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				bind(addr, port);
				inet::socket::listen(10);
			}

			void listen(int port, int conn = 10) {
				init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				bind("0.0.0.0", port);
				inet::socket::listen(conn);				
			} 

			inet::tcp_socket accept() {
				int c = sizeof(sockaddr_in);
				sockaddr_in caddr;
				memset(&caddr, 0, sizeof(caddr));
				int cfd = ::accept( fd, (sockaddr*)&caddr, (socklen_t*)&c );

				gxx::inet::tcp_socket sock;
				sock.fd = cfd;
				return sock;
			}
		};
	}
}

#endif