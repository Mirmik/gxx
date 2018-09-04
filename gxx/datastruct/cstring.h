#ifndef GXX_DATASTRUCT_CSTRING_H
#define GXX_DATASTRUCT_CSTRING_H

#include <sys/cdefs.h>
#include <gxx/datastruct/allocator.h>

struct cstring {
	void * data;
	size_t size;
	
	allocator_t* alloc;
};

__BEGIN_DECLS

static inline void cstring_setview(
	struct cstring* str, 
	void* data, 
	size_t size
) {
	str->data = data;
	str->size = size;
	str->alloc = NULL;
}

static inline void cstring_strdup(
	struct cstring* str, 
	const void* data, 
	size_t size,
	allocator_t* alloc
) {
	str->data = alloc->allocate(size);
	memcpy(str->data, data, size);
	str->size = size;
	str->alloc = alloc;
}

static inline void cstring_destroy(struct cstring* str) {
	if (str->alloc) str->alloc->deallocate(str->data);
}

__END_DECLS

#endif