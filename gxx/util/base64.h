#ifndef GXX_UTIL_BASE64_H
#define GXX_UTIL_BASE64_H

#include <string>

namespace gxx {
	//bool is_base64(unsigned char c);
	std::string base64_encode(const uint8_t *indata, size_t size);
	std::string base64_decode(std::string const& encoded_string);
}

#endif