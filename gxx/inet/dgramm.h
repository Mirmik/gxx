#ifndef GXX_DATAGRAMM_SOCKET_H
#define GXX_DATAGRAMM_SOCKET_H

#include <gxx/inet/socket2.h>

namespace gxx { 
	namespace inet {
		struct datagramm_socket : public inet::socket {
			datagramm_socket(int domain, int type, int proto) : inet::socket(domain, type, proto) {}

			void sendto(gxx::inet::hostaddr haddr, int port, const char* data, size_t size) {
		 		struct sockaddr_in addr;
				memset(&addr, 0, sizeof(addr));

				addr.sin_family = family;    
    			addr.sin_addr.s_addr = haddr.addr;  //INADDR_ANY = 0.0.0.0
    			addr.sin_port = htons(port);

    			return ::sendto(sock, data, size, 0, (sockaddr*) &addr, &sz);
			}
			
			gxx::inet::netaddr recvfrom(char* data, size_t maxsize) {
		 		struct sockaddr_in si_other;
		 		unsigned int sz;
		 		::recvfrom(sock, data, maxsize, 0, (sockaddr*) &si_other, &sz);

		 		return gxx::inet::netaddr(si_other.addr.addr, si_other.port);
			}
		};
	
		struct udp_socket : public datagramm_socket {
			udp_socket() : datagramm_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) {}
		};
	
		/*struct rdm_socket : public datagramm_socket {
			rdm_socket() {
				sock = ::socket(AF_INET, SOCK_RDM, 0);
			}
		};*/
	}
}

#endif