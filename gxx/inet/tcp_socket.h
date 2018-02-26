#ifndef GXX_INET_TCP_SOCKET_H
#define GXX_INET_TCP_SOCKET_H

#include <gxx/io/iostream.h>
#include <gxx/inet/socket2.h>
#include <stdio.h>
#include <unistd.h>

namespace gxx {
	namespace inet {
		struct tcp_socket : public inet::socket, public io::iostream {
			tcp_socket() : socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) {}
			tcp_socket(gxx::inet::hostaddr addr, int port) : tcp_socket() {
				connect(addr, port);
			} 
			
			int writeData(const char* data, size_t size) override {
				return ::write(fd, data, size);
			}

			int readData(char* data, size_t size) override {
				return ::read(fd, data, size);
			}
		};
	}
}

#endif