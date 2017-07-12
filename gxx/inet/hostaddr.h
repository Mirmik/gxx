#ifndef GXX_INETADDR_H
#define GXX_INETADDR_H

#include <ctype.h>
#include <string>

#include <gxx/string.h>

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
	};
}

#endif