#ifndef GXX_IO_SOCKET2_H
#define GXX_IO_SOCKET2_H

#include <gxx/inet/hostaddr.h>
//#include <netinet/in.h>
//#include <sys/socket.h>
#include <string.h>

namespace gxx { 
	namespace inet {
		struct socket {
			int fd;

			bool good() {
				return fd >= 0;
			}

			socket() = default;
			socket(const socket& oth) = default;
			socket(socket&& oth) = default;
			socket& operator=(const socket& oth) = default;
			socket& operator=(socket&& oth) = default;

			ssize_t send(const char* data, size_t size, int flags);
			ssize_t recv(char* data, size_t size, int flags);

			int init(int domain, int type, int proto); //posix ::socket
			int bind(const hostaddr& haddr, uint16_t port, int family);
			int connect(const hostaddr& haddr, uint16_t port, int family);
			int listen(int conn);

			int nodelay(bool en);
			int nonblock(bool en);
			int reusing(bool en);
			
			[[deprecated]]
			int blocking(bool en);
			
			int close();
		};
	}
}

#endif
