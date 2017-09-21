#ifndef GXX_DEBUG_FUNCTIONS_H
#define GXX_DEBUG_FUNCTIONS_H

#include <gxx/debug/debug_ostream.h>

namespace gxx {
	template<typename ... Args>
	void debug(Args ... args) {
		debug_ostream dout;
		dout.print("gxx::debug: ");
		dout.format(std::forward<Args>(args) ...);
	}
}

#endif