#ifndef GXX_STRING_H
#define GXX_STRING_H

#include <vector>
#include <string>

namespace gxx {
	using strvec = std::vector<std::string>;

	strvec split(const std::string& str, char delim);
}

#endif