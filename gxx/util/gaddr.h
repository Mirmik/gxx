#include <gxx/util/hexer.h>
#include <string>

namespace gxx {
	static inline std::string gaddr(const char* str, size_t sz) {
		uint8_t buf[sz];
		int len = hexer(buf, sz, str, sz);
		if (len < 0) throw std::exception();
		return std::string((char*)buf, len);
	}

	static inline std::string gaddr(const std::string& str) {
		return gaddr(str.data(), str.size());
	}

	static inline std::string gaddr(const char* str) {
		return gaddr(str, strlen(str));
	}

}