#ifndef GENOS_UTILXX_BUFFER_H
#define GENOS_UTILXX_BUFFER_H

#include <gxx/object_buffer.h>

namespace gxx {
	using buffer = object_buffer<char>;
	using allocated_buffer = allocated_object_buffer<char>;

	allocated_buffer allot_buffer(size_t sz) { return allocated_buffer(sz); }
}

#endif 