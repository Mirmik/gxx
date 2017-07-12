#include <gxx/string.h>

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