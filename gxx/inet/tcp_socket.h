#ifndef GXX_INET_TCP_SOCKET_H
#define GXX_INET_TCP_SOCKET_H

#include <gxx/io/iostream.h>
#include <gxx/inet/socket.h>
#include <stdio.h>
#include <unistd.h>

namespace gxx {
	namespace inet {
		struct tcp_socket : public inet::socket, public io::iostream {
			//do nothing
			tcp_socket() = default;

			//
			tcp_socket(const tcp_socket& oth) = default;
			tcp_socket(tcp_socket&& oth) = default;
			tcp_socket& operator=(const tcp_socket& oth) = default;
			tcp_socket& operator=(tcp_socket&& oth) = default;

			//create socket
			int init();

			int connect(gxx::inet::hostaddr addr, uint16_t port);

			//create and connect
			tcp_socket(gxx::inet::hostaddr addr, uint16_t port);
			
			//io api implementation
			ssize_t writeData(const char* data, size_t size) override;
			ssize_t readData(char* data, size_t size) override;
		};
	}
}

#endif
