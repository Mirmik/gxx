#ifndef GXX_DEBUG_DEBUG_OSTREAM_H
#define GXX_DEBUG_DEBUG_OSTREAM_H

#include <gxx/debug/dprint.h>
#include <gxx/io/ostream.h>

namespace gxx {
	class debug_ostream : public gxx::io::ostream {
		int32_t writeData(const char *data, size_t maxSize) {
			debug_write(data, maxSize);
			return maxSize;
		}
	};
}

#endif