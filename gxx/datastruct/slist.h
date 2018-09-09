#ifndef UTIL_SLIST_H_
#define UTIL_SLIST_H_

//#include <inttypes.h>
#include <sys/cdefs.h>
#include <gxx/util/member.h>

struct slist_head {
	struct slist_head *next;
};

#define SLIST_HEAD_INIT(name) { &(name) }

#define SLIST_HEAD(name) \
	struct slist_head name = SLIST_HEAD_INIT(name)

__BEGIN_DECLS

static inline void slist_init(struct slist_head* head) {
	head->next = head;
} 

static inline int slist_empty(struct slist_head* head) {
	return head->next == head;
} 

static inline void slist_add(struct slist_head* link, struct slist_head* head) {
	link->next = head->next;
	head->next = link;
}

static inline struct slist_head* slist_pop_first(struct slist_head* head) {
	struct slist_head* ret = head->next;
	if (ret == head) return NULL;
	head->next = ret->next;
	return ret;
}

__END_DECLS

#define slist_entry(ptr, type, member) \
mcast_out(ptr, type, member)

#define slist_first_entry(ptr, type, member) \
slist_entry((ptr)->next, type, member)

#define slist_for_each(pos, head) \
for (pos = (head)->next; pos != (head); pos = pos->next)

#define slist_for_each_entry(pos, head, member)					\
for (pos = slist_first_entry(head, __typeof__(*pos), member);	\
&pos->member != (head);											\
pos = slist_next_entry(pos, member))

#endif