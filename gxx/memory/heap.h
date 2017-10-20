#ifndef GXX_MEMORY_HEAP_H
#define GXX_MEMORY_HEAP_H

#include <gxx/slist.h>
#include <stdlib.h>

namespace gxx {
	namespace memory {
		class heap {
			struct freelist {
				slist_head lnk;
				size_t sz;
			};

			gxx::slist<freelist, &freelist::lnk> fl;
		};
	}
}

#endif