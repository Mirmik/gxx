#ifndef GXX_BYTEARRAY_H
#define GXX_BYTEARRAY_H

#include <gxx/buffer.h>

namespace gxx {
	class bytearray : public gxx::buffer {
	public:
		bytearray(const char* data, size_t sz) : gxx::buffer(new char[sz], sz) {
			memcpy(gxx::buffer::data(), data, sz);
		}
	};
}

#endif