#ifndef GXX_MESSENGER_H
#define GXX_MESSENGER_H

#include <inttypes.h>

using msgr_id = uint16_t;

#include <gxx/messenger/query.h>
#include <gxx/dlist.h>
#include <gxx/datastruct/hlist_head.h>

namespace gxx {

	namespace msg {
		class messenger {
			gxx::dlist<gxx::msg::query, &gxx::msg::query::prntlnk> child_list;
			gxx::dlist<gxx::msg::query, &gxx::msg::query::traclnk> guest_list;

		public:
			msgr_id id;

			//hashtable manage
			hlist_node hlnk;
		};
	}
}

#include <gxx/messenger/msgrtable.h>

#endif