#ifndef GXX_INETADDR_H
#define GXX_INETADDR_H

#include <ctype.h>
#include <string>

#include <gxx/util/string.h>
#include <gxx/print.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace gxx {
	class hostaddr {
	public:
		uint32_t addr;
		hostaddr() : addr(0) {}
		hostaddr(uint32_t addr) : addr(addr) {}
		
		hostaddr(const char* str) {
			addr = ::inet_addr(str);
		}

		hostaddr(const std::string& str) : hostaddr(str.c_str()) {}

		size_t printTo(gxx::io::ostream& o) const {
			return o.printhex(addr);
		}
		
	};

	namespace inet {
		static constexpr const char* localhost = "127.0.0.1"; 
		using hostaddr = gxx::hostaddr;

		struct netaddr {
			hostaddr addr;
			int32_t port;
			netaddr(unsigned long addr, unsigned short port) : addr(ntohl(addr)), port(ntohs(port)) {}
			netaddr(){};
			size_t printTo(gxx::io::ostream& o) const {
				return gxx::fprint_to(o, "(h:{},p:{})", addr, port);
			}
		};
	}
}

#endif
