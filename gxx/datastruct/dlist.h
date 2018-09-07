#ifndef GENOS_DLIST_HEAD
#define GENOS_DLIST_HEAD

//#include <inttypes.h>
#include <sys/cdefs.h>
#include <gxx/util/member.h>

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#define DLIST_POISON1  ((void *) 0x00100100)
#define DLIST_POISON2  ((void *) 0x00200200)

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
struct dlist_head {
	struct dlist_head *next, *prev;
};

#define DLIST_HEAD_INIT(name) { &(name), &(name) }

#define DLIST_HEAD(name) \
	struct dlist_head name = DLIST_HEAD_INIT(name)

__BEGIN_DECLS

static inline void dlist_init(struct dlist_head* head) {
	head->next = head->prev = head;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __dlist_add(struct dlist_head *_new, struct dlist_head *next, struct dlist_head *prev) {
	_new->prev = prev;
	_new->next = next;
	next->prev = _new;
	prev->next = _new;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void dlist_add_next(struct dlist_head* _new, struct dlist_head* head) {
	__dlist_add(_new, head->next, head);
}
#define dlist_add(a,b) dlist_add_next(a,b)

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void dlist_add_prev(struct dlist_head* _new, struct dlist_head* head) {
	__dlist_add(_new, head, head->prev);
}
#define dlist_add_tail(a,b) dlist_add_prev(a,b)

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __dlist_del(struct dlist_head * prev, struct dlist_head * next) {
	next->prev = prev;
	prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is
 * in an undefined state.
 */
static inline void dlist_del(struct dlist_head *entry) {
	__dlist_del(entry->prev, entry->next);
	entry->next = DLIST_POISON1;
	entry->prev = DLIST_POISON2;
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void dlist_del_init(struct dlist_head *entry) {
	__dlist_del(entry->prev, entry->next);
	dlist_init(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void dlist_move(struct dlist_head *list, struct dlist_head *head) {
        __dlist_del(list->prev, list->next);
        dlist_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void dlist_move_tail(struct dlist_head *list, struct dlist_head *head) {
        __dlist_del(list->prev, list->next);
        dlist_add_tail(list, head);
}
#define dlist_move_prev(a,b) dlist_move_tail(a,b)

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int dlist_empty(const struct dlist_head *head) {
	return head->next == head;
}

/**
 * @fn dlist_first_or_null()
 * @fn dlist_last_or_null()
 *
 * Get first/last link with null as a fallback return value
 * for case of an empty list.
 */
static inline struct dlist_head *dlist_first_or_null(const struct dlist_head *list) {
	return (!dlist_empty(list) ? list->next : NULL);
}

static inline struct dlist_head *dlist_last_or_null(const struct dlist_head *list) {
	return (!dlist_empty(list) ? list->prev : NULL);
}

__END_DECLS

#define dlist_entry(ptr, type, member) \
	mcast_out(ptr, type, member)

#define dlist_next_entry(pos, member) \
	dlist_entry((pos)->member.next, __typeof__(*(pos)), member)

#define dlist_prev_entry(pos, member) \
	dlist_entry((pos)->member.prev, __typeof__(*(pos)), member)

#define dlist_first_entry(ptr, type, member) \
	dlist_entry((ptr)->next, type, member)

#define dlist_last_entry(ptr, type, member) \
	dlist_entry((ptr)->prev, type, member)

#define dlist_for_each(pos, head) \
for (pos = (head)->next; pos != (head); pos = pos->next)

#define dlist_for_each_safe(pos, n, head) \
for (pos = (head)->next, n = pos->next; pos != (head); \
pos = n, n = pos->next)

#define dlist_for_each_entry(pos, head, member)					\
for (pos = dlist_first_entry(head, __typeof__(*pos), member);	\
&pos->member != (head);											\
pos = dlist_next_entry(pos, member))

#define dlist_for_each_entry_safe(pos, n, head, member)			\
for (pos = dlist_first_entry(head, __typeof__(*pos), member),	\
n = dlist_next_entry(pos, member);			\
&pos->member != (head); 					\
pos = n, n = dlist_next_entry(n, member))
	
#endif
