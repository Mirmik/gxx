#ifndef GXX_MESSANGER_QUERY_H
#define GXX_MESSANGER_QUERY_H

#include <gxx/datastruct/dlist_head.h>

namespace gxx {
	namespace msg {
		class messenger;

		enum class QueryFlags : uint16_t {
			NoReturn,
			WithoutParent,
			DataDeallocate,
		};

		class query {
			void* data;
			uint16_t flags;

		public:
			msgr_id creator;
			messenger* parent;

		public:
			//manage fields
			dlist_head prntlnk;
			dlist_head traclnk;

		public:
			//query(messenger* parent, )
		};
	}
}

#endif