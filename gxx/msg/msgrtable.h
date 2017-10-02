#ifndef GXX_MESSANGER_MSGRTABLE_H
#define GXX_MESSANGER_MSGRTABLE_H

#include <gxx/hashtable.h>

namespace gxx {
	namespace msg {
		class gate {
			virtual int send(const char* data, size_t size);
		};

		class msgrtable {
			gxx::static_hashtable <10, messenger, msgr_id, &messenger::hlnk> htable;
		};
	} 
}

#endif