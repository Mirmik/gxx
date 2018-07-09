#ifndef GXX_STRING_H
#define GXX_STRING_H

#include <cstdint>
#include <gxx/util/asciiconvert.h>
#include <list>
#include <vector>
#include <string>

namespace gxx {
	using strvec = std::vector<std::string>;
	using strlst = std::list<std::string>;

	strvec split(const std::string& str, char delim);
	std::string join(const strvec&, char delim);

	static inline std::string serialstr8(const std::string& str) {
		std::string ret;
		ret.push_back((uint8_t)str.size());
		ret.append(str);
		return ret;
	}

	static inline std::string serialstr8(const char* data, size_t size) {
		std::string ret;
		ret.push_back((uint8_t) size);
		ret.append(data, size);
		return ret;
	}

	static inline std::string dstring(const void* data, size_t size) {
		std::string ret;
		char* it = (char*) data;
		char* eit = it + size;

		for (;it!=eit;++it) {
			if (isprint(*it)) ret.push_back(*it);
			else if (*it == '\n') ret.append("\\n", 2);
			else if (*it == '\t') ret.append("\\t", 2);
			else if (*it == '\\') ret.append("\\\\", 2);
			else { 
				uint8_t hi = byte2sym((*it & 0xF0) >> 4);
				uint8_t low = byte2sym(*it & 0x0F);
				ret.append("\\x", 2);
				ret.push_back(hi);  
				ret.push_back(low); 
			}
		}
		return ret;
	}
}

#endif