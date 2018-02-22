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

			socket(int domain, int type, int proto) {
				fd = ::socket(domain, type, proto);
				
				if (fd < 0) {
					gxx::fprintln("warn: {}", strerror(errno));
				}
			}

			int bind(gxx::inet::hostaddr haddr, int port, int family = PF_INET) {
				struct sockaddr_in addr;
				memset(&addr, 0, sizeof(addr));

				addr.sin_family = family;    
    			addr.sin_addr.s_addr = htonl(haddr.addr);  //INADDR_ANY = 0.0.0.0
    			addr.sin_port = htons(port);

    			return ::bind(fd, (sockaddr*) &addr, sizeof(struct sockaddr_in)); 
			}
		};
	}
}

#endif