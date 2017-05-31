#ifndef GXX_LOGGER_TARGET_H
#define GXX_LOGGER_TARGET_H

#include <gxx/debug/dprint.h>

namespace gxx {
	namespace log {
		class target {
		public:
			virtual void log(const char* str) = 0;
		};
	}
}

#endif