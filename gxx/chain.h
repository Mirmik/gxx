#ifndef GXX_CHAIN_H
#define GXX_CHAIN_H

#include <vector>
#include <cstdint>

#include <gxx/object_buffer.h>

namespace gxx {
	struct chain;

	using chainfunc_t = void*(*)(void* ptr, int8_t* sts);

	struct chain {
		void* data;
		uint16_t size;
		chain(gxx::object_buffer<chainfunc_t> functape, gxx::buffer argstape);
		~chain();
		int8_t exec();
	};
}

#endif 