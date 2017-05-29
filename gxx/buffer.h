#ifndef GENOS_UTILXX_BUFFER_H
#define GENOS_UTILXX_BUFFER_H

#include <string.h>
#include <gxx/object_buffer.h>

namespace gxx {
	class buffer : public object_buffer<char> {
	public:
		buffer(const char* ptr) : object_buffer<char>((char*)ptr, strlen(ptr)) {}
	};

	using allocated_buffer = allocated_object_buffer<char>;

	allocated_buffer allot_buffer(size_t sz);// { return allocated_buffer(sz); }
}

#endif 