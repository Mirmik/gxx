#ifndef GXX_STRING_H
#define GXX_STRING_H

#include <vector>
#include <string>

namespace gxx {
	using strvec = std::vector<std::string>;

	strvec split(const std::string& str, char delim) {
		gxx::strvec outvec;

		char* strt;
		char* ptr = (char*)str.data();
		char* end = (char*)str.data() + str.size();
		
		while(true) {
			strt = ptr;

			while (*ptr != delim && ptr != end) ptr++;
			outvec.emplace_back(strt, ptr - strt);		

			if (*ptr == delim) ptr++;
			else break;
		}

		return outvec;
	} 
}

#endif