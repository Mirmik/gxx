#ifndef GXX_IO_SOCKET2_H
#define GXX_IO_SOCKET2_H

#include <gxx/inet/hostaddr.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

namespace gxx { 
	namespace inet {
		struct socket {
			int fd;

			bool good() {
				return fd >= 0;
			}

			socket() = default;

			int init(int domain, int type, int proto); //posix ::socket
			int bind(gxx::inet::hostaddr haddr, int port, int family = PF_INET);
			int connect(gxx::inet::hostaddr haddr, int port, int family = PF_INET);
			int listen(int conn);

			int nodelay(bool en);
			int blocking(bool en);
			int reusing(bool en);

			int close();
		};
	}
}

#endif