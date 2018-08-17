#ifndef GENOS_DLIST_HEAD
#define GENOS_DLIST_HEAD

#include <inttypes.h>
#include <sys/cdefs.h>

#include <gxx/util/member.h>

struct dlist_head {
	struct dlist_head* next;
	struct dlist_head* prev;
};

#define DLIST_HEAD_INIT(name) { &(name), &(name) }

#define DLIST_HEAD(name) \
	struct dlist_head name = DLIST_HEAD_INIT(name)

__BEGIN_DECLS

static inline void dlist_init(struct dlist_head* head) {
	head->next = head;
	head->prev = head;
}

static inline void dlist_head_init(struct dlist_head* head) {
	head->next = head;
	head->prev = head;
}

static inline void dlist_init_list(struct dlist_head* head) {
	head->next = head;
	head->prev = head;
}

static inline int8_t dlist_is_empty(const struct dlist_head* head) {
	return head == head->next;
}
#define dlist_empty(arg) dlist_is_empty(arg)

static inline void __dlist_add(struct dlist_head *_new, struct dlist_head *next, struct dlist_head *prev) {
	_new->prev = prev;
	_new->next = next;
	next->prev = _new;
	prev->next = _new;
}

static inline void dlist_add_next(struct dlist_head* _new, struct dlist_head* head) {
	__dlist_add(_new, head->next, head);
}
#define dlist_add_front(a,b) dlist_add_next(a,b)
#define dlist_add(a,b) dlist_add_next(a,b)

static inline void dlist_add_prev(struct dlist_head* _new, struct dlist_head* head) {
	__dlist_add(_new, head, head->prev);
}
#define dlist_add_back(a,b) dlist_add_prev(a,b)
#define dlist_add_tail(a,b) dlist_add_prev(a,b)

static inline void __dlist_del(struct dlist_head* head) {
	head->prev->next = head->next;
	head->next->prev = head->prev;
}

static inline void dlist_del(struct dlist_head* head) {
	__dlist_del(head);
	dlist_init(head);	
}
#define dlist_del_init(x) dlist_del(x)

static inline void dlist_move_next(struct dlist_head* lst, struct dlist_head* head) {
	__dlist_del(lst);
	dlist_add_next(lst, head);
}
#define dlist_move_back(a,b) dlist_move_prev(a,b)

static inline void dlist_move_prev(struct dlist_head* lst, struct dlist_head* head) {
	__dlist_del(lst);
	dlist_add_prev(lst, head);
}
#define dlist_move_back(a,b) dlist_move_prev(a,b)

/**
 * @fn dlist_first()
 * @fn dlist_last()
 *
 * Get first/last link of a non-empty list.
 */
#define dlist_first dlist_next
#define dlist_last  dlist_prev

/**
 * @fn dlist_next()
 * @fn dlist_prev()
 *
 * Get next/prev link of a non-empty list.
 */

static inline struct dlist_head *dlist_next(const struct dlist_head *list) {
	return list->next;
}

static inline struct dlist_head *dlist_prev(const struct dlist_head *list) {
	return list->prev;
}

/**
 * @fn dlist_first_or_null()
 * @fn dlist_last_or_null()
 *
 * Get first/last link with null as a fallback return value
 * for case of an empty list.
 */

static inline struct dlist_head *dlist_first_or_null(const struct dlist_head *list) {
	return (!dlist_empty(list) ? dlist_first(list) : NULL);
}

static inline struct dlist_head *dlist_last_or_null(const struct dlist_head *list) {
	return (!dlist_empty(list) ? dlist_last(list) : NULL);
}

#define dlist_next_entry(pos, member) \
dlist_entry((pos)->member.next, __typeof__(*(pos)), member)

#define dlist_prev_entry(pos, member) \
dlist_entry((pos)->member.prev, __typeof__(*(pos)), member)

__END_DECLS

#define dlist_entry(ptr, type, member) \
mcast_out(ptr, type, member)

//#define dlist_next_entry(pos, member) \
//dlist_entry((pos)->member.next, __typeof__(*(pos)), member)

//#define dlist_prev_entry(pos, member) \
//dlist_entry((pos)->member.prev, __typeof__(*(pos)), member)

#define dlist_first_entry(ptr, type, member) \
dlist_entry((ptr)->next, type, member)

#define dlist_last_entry(ptr, type, member) \
dlist_entry((ptr)->prev, type, member)

#define dlist_for_each(pos, head) \
for (pos = (head)->next; pos != (head); pos = pos->next)

#define dlist_for_each_safe(pos, n, head) \
for (pos = (head)->next, n = pos->next; pos != (head); \
pos = n, n = pos->next)

#define dlist_for_each_entry(pos, head, member)				\
for (pos = dlist_first_entry(head, __typeof__(*pos), member);	\
&pos->member != (head);					\
pos = dlist_next_entry(pos, member))

#define dlist_for_each_entry_safe(pos, n, head, member)			\
for (pos = dlist_first_entry(head, __typeof__(*pos), member),	\
n = dlist_next_entry(pos, member);			\
&pos->member != (head); 					\
pos = n, n = dlist_next_entry(n, member))
	
#endif
