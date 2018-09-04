#ifndef GXX_DATASTRUCT_TRENT_H
#define GXX_DATASTRUCT_TRENT_H

/**
	Pure C trent implementation.
	trent - is script-language like object.
	It can be integer, numerical, string, dictionary, list or nil type. 
*/

#include <gxx/datastruct/dlist.h>
#include <gxx/datastruct/cstring.h>

enum TrentType {
	TRENT_NIL = 0,
	TRENT_INT = 1,
	TRENT_NUM = 2,
	TRENT_STR = 3,
	TRENT_LIST = 4,
	TRENT_DICT = 5,
	TRENT_TABL = 6,
};

typedef struct trent_s {
	struct dlist_head lnk;
	struct trent_s* parent;
	struct cstring name;
	uint8_t type;

	union {
		long long 			m_int;
		long double 		m_num;
		struct cstring  	m_str;
		struct dlist_head 	m_childs;
	};
} trent_t;

static inline void trent_init(trent_t* tr, trent_t* parent) {
	dlist_init(&tr->lnk);
	tr->parent = parent;
	tr->flags = 0;
}

static inline void trent_init_int(trent_t* tr, trent_t* parent, long long val) {
	trent_init(tr, parent);
	tr->type = TRENT_INT;
	tr->m_int = val;
}

void trent_init_num(trent_t* tr, trent_t* parent, long double val);
void trent_init_str_view(trent_t* tr, trent_t* parent, const char* ptr, size_t sz);
void trent_init_str_copy(trent_t* tr, trent_t* parent, const char* ptr, size_t sz);
void trent_init_str(trent_t* tr, trent_t* parent, const cstring* str);
void trent_init_tabl(trent_t* tr, trent_t* parent, uint8_t tableType);

void trent_setname_view(trent_t* tr, const void* name, size_t len);
void trent_setname_copy(trent_t* tr, const void* name, size_t len);
void trent_setname(trent_t* tr, const cstring* str);

int trent_addchild(trent_t* parent, trent_t* child);

int trent_addchild_int(trent_t* tr);
int trent_addchild_num(trent_t* tr);
int trent_addchild_str(trent_t* tr);
int trent_addchild_dict(trent_t* tr);
int trent_addchild_list(trent_t* tr);
int trent_addchild_tabl(trent_t* tr);

//results: true: 1, false: 0, error: -1
int trent_equal(trent_t* a, trent_t* b) {}

#endif