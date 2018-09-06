#ifndef GXX_DATASTRUCT_POOL_H
#define GXX_DATASTRUCT_POOL_H

#include <gxx/datastruct/slist.h>

struct memzone_head {
	struct slist_head lnk;
	void* zone;
	size_t size;
};

struct pool_head {
	struct slist_head free_blocks;
	size_t elemsz;
};

struct zonepool_head {
	struct pool_head pool;
	struct slist_head zones;
};

__BEGIN_DECLS

static inline void pool_init(struct pool_head* head, size_t elemsz) {
	slist_init(&head->free_blocks);
	head->elemsz = elemsz;
}

static inline void pool_engage(struct pool_head* pool, void* zone, size_t size) {
	char* stop = (char*)zone + size;
	char* it = (char*)zone;

	while(it < stop) {
		slist_add((slist_head*)it, &pool->free_blocks);
		it += pool->elemsz;
	}
}

static inline void* pool_alloc(struct pool_head* head) {
	return (void*) slist_pop_first(&head->free_blocks);
}

static inline void pool_free(struct pool_head* head, void* ptr) {
	slist_add((slist_head*) ptr, &head->free_blocks);
}





static inline void memzone_init(struct memzone_head* head, void* zone, size_t size) {
	head->zone = zone; 
	head->size = size;
}


static inline void pool_engage_memzone(struct pool_head* pool, struct memzone_head* zone) {

}

static inline void pool_empty_zones(struct pool_head* pool, int* retarr);

__END_DECLS

#endif