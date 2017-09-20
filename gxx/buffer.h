#ifndef GENOS_UTILXX_BUFFER_H
#define GENOS_UTILXX_BUFFER_H

#include <string>
#include <cstring>
#include <gxx/object_buffer.h>

namespace gxx {
	class buffer {
		char* buf;
		size_t sz;
	public:
		buffer() : buf(nullptr), sz(0) {}
		buffer(const char* buf, size_t sz) : buf((char*)buf), sz(sz) {}

		bool empty() { return buf == nullptr; }

		bool operator==(const buffer& other) const {
			return (sz == other.sz) && (strncmp(buf, other.buf, std::min(sz, other.sz)) == 0);
		}

		ACCESSOR(data, buf);
		ACCESSOR(size, sz);
	};
}

#endif 