#ifndef GXX_DEBUG_FUNCTIONS_H
#define GXX_DEBUG_FUNCTIONS_H

#include <gxx/format.h>

namespace gxx {
	template<typename ... Args>
	void debug(Args ... args) {
		dpr("gxx::debug: ");
		dprln(std::forward<Args>(args) ...);
	}
}

#endif