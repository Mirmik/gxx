#ifndef GXX_DATAGRAMM_SOCKET_H
#define GXX_DATAGRAMM_SOCKET_H

#include <gxx/inet/socket2.h>
#include <gxx/print.h>

namespace gxx { 
	namespace inet {
		struct datagramm_socket : public inet::socket {
			datagramm_socket(int domain, int type, int proto) : inet::socket(domain, type, proto) {}

			int sendto(gxx::inet::hostaddr haddr, int port, const char* data, size_t size) {
		 		struct sockaddr_in addr;
				memset(&addr, 0, sizeof(addr));

				addr.sin_family = PF_INET;    
    			addr.sin_addr.s_addr = haddr.addr;  //INADDR_ANY = 0.0.0.0
    			addr.sin_port = htons(port);

    			return ::sendto(sock, data, size, 0, (sockaddr*) &addr, sizeof(sockaddr_in));
			}
			
			int recvfrom(char* data, size_t maxsize, gxx::inet::netaddr* inaddr) {
		 		struct sockaddr_in si_other;
		 		unsigned int sz = sizeof(sockaddr_in);
		 		int ret = ::recvfrom(sock, data, maxsize, 0, (sockaddr*) &si_other, &sz);
		 		
		 		if (ret < 0) {
		 			gxx::println(strerror(errno));
		 		}

		 		if (inaddr) *inaddr = gxx::inet::netaddr(si_other.sin_addr.s_addr, si_other.sin_port);
		 		return ret;
			}
		};
	
		struct udp_socket : public datagramm_socket {
			udp_socket() : datagramm_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) {}
			udp_socket(gxx::inet::hostaddr addr, int port) : udp_socket() {
				bind(addr, port);
			}  
		};

		struct rdm_socket : public datagramm_socket {
			rdm_socket() : datagramm_socket(AF_INET, SOCK_RDM, 0) {}
			rdm_socket(gxx::inet::hostaddr addr, int port) : rdm_socket() {
				bind(addr, port);
			}  
		};
	
		/*struct rdm_socket : public datagramm_socket {
			rdm_socket() {
				sock = ::socket(AF_INET, SOCK_RDM, 0);
			}
		};*/
	}
}

#endif