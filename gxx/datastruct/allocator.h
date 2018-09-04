#ifndef GXX_DATASTRUCT_ALLOCATOR_H
#define GXX_DATASTRUCT_ALLOCATOR_H

#include <stdint.h>

typedef struct allocator_s {
	void*(*allocate)(size_t);
	void(*deallocate)(void*);
} allocator_t;

#endif