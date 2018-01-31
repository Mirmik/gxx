#ifndef GXX_MSG_MSG_H
#define GXX_MSG_MSG_H

namespace gxx {
	namespace msg {
		class query {
			gxx::buffer buf;
			dlist_head lnk;
		};

		class socket {
			virtual int transmit(query& q) = 0;			
		};
	}
}

#endif