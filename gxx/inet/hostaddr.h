#ifndef GXX_INETADDR_H
#define GXX_INETADDR_H

#include <ctype.h>
#include <string>

#include <gxx/util/string.h>
#include <gxx/print.h>

//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>

namespace gxx {
	class hostaddr {
	public:
		uint32_t addr;
		hostaddr() : addr(0) {}
		hostaddr(uint32_t addr) : addr(addr) {}
		
		hostaddr(const char* str) {
                    if (isdigit(*str)) {
                        gxx::strvec nums = gxx::split(str, '.');
                        addr =
                                atoi(nums[0].c_str()) << 24 |
                                atoi(nums[1].c_str()) << 16 |
                                atoi(nums[2].c_str()) << 8 |
                                atoi(nums[3].c_str());
                    }
		}

		hostaddr(const std::string& str) : hostaddr(str.c_str()) {}

		size_t printTo(gxx::io::ostream& o) const {
			return o.printhex(addr);
		}
		
		bool operator == (const hostaddr& oth) {
			return oth.addr == addr;
		}
	};

	namespace inet {
		static constexpr const char* localhost = "127.0.0.1"; 
		using hostaddr = gxx::hostaddr;

		struct netaddr {
			hostaddr addr;
			int32_t port;
                        netaddr(unsigned long addr, unsigned short port);
                        netaddr() = default;
			size_t printTo(gxx::io::ostream& o) const {
				return gxx::fprint_to(o, "(h:{},p:{})", addr, port);
			}
		};
	}
}

#endif
