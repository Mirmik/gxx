#ifndef GENOS_DATASTRUCT_RING_HEAD_H
#define GENOS_DATASTRUCT_RING_HEAD_H

#include <sys/cdefs.h>

struct ring_head {
	size_t head;
	size_t tail;
	size_t size;
};

__BEGIN_DECLS

static inline struct ring_head* ring_init(struct ring_head* r, size_t r_size) {
	r->size = r_size;
	r->head = 0;
	r->tail = 0;
	return r;
}

static inline struct ring_head* ring_fixup_head(struct ring_head* r) {
	while (r->head >= r->size) r->head -= r->size;
	return r; 
}

static inline struct ring_head* ring_fixup_tail(struct ring_head* r) {
	while (r->tail >= r->size) r->tail -= r->size;
	return r; 
}

static inline int8_t ring_empty(struct ring_head* r) {
	return r->head == r->tail;
}

static inline int8_t ring_full(struct ring_head* r) {
	return r->head == (r->tail ? r->tail : r->size) - 1;
}

static inline size_t ring_avail(struct ring_head* r) { 
		return (r->head >= r->tail) ? 
		r->head - r->tail : 
		r->size + r->head - r->tail; 
}

static inline size_t ring_room(struct ring_head* r) {
	return (r->head >= r->tail) ? 
	r->size - 1 + ( r->tail - r->head ) : 
	( r->tail - r->head ) - 1;
}

static inline struct ring_head* ring_move_head_one(struct ring_head* r)
{
	++r->head;
	if (r->head == r->size) r->head = 0;
	return r;
}

static inline struct ring_head* ring_move_tail_one(struct ring_head* r) {
	++r->tail;
	if (r->tail == r->size) r->tail = 0;
	return r;
}

static inline struct ring_head* ring_move_head(struct ring_head* r, size_t bias) {
	r->head += bias;
	ring_fixup_head(r);
	return r;
}

static inline struct ring_head* ring_move_tail(struct ring_head* r, size_t bias) {
	r->tail += bias;
	ring_fixup_tail(r);
	return r;
}

static inline int ring_putc(struct ring_head* r, char* buffer, char c) {
	if (ring_full(r)) return 0;	
	*(buffer + r->head) = c;
	ring_move_head_one(r);
	return 1;
}

static inline int ring_getc(struct ring_head* r, const char* buffer) {
	if (ring_empty(r)) return -1;	
	char c = *(buffer + r->tail);
	ring_move_tail_one(r);
	return c;
}

static inline int ring_read(struct ring_head* r, const char* buffer, char* data, size_t size) {
	int c;
	int ret = 0;
	while(size--) {
		c = ring_getc(r, buffer); 
		if(c == -1) return ret;
		*data++ = c;
		ret++;
	}
	return ret;
}

static inline int ring_write(struct ring_head* r, char* buffer, const char* data, size_t size) {
	int ret = 0;
	while(size--) {
		if(ring_putc(r, buffer, *data++) == 0) {
			return ret;
		};
		ret++;
	}
	return ret;
}

#define ring_for_each(n,r) \
for(size_t n = (r)->tail; n != (r)->head; n = (n+1)%(r)->size)

__END_DECLS

#endif