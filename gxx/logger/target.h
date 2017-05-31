#ifndef GXX_LOGGER_TARGET_H
#define GXX_LOGGER_TARGET_H

#include <gxx/datastruct/dlist_head.h>
#include <gxx/debug/dprint.h>

namespace gxx {
	namespace log {
		class target {
		public:
			dlist_head manage_link;
			virtual void log(const char* str) = 0;
		};
	}
}

#endif