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

static inline void slist_add_next(struct slist_head* link, struct slist_head* head) {
	link->next = head->next;
	head->next = link;
}

static inline slist_head* slist_pop_first(struct slist_head* head) {
	slist_head* ret = head->next;
	if (ret == head) return NULL;
	head->next = ret->next;
	return ret;
}

__END_DECLS

#endif /* UTIL_SLIST_H_ */
