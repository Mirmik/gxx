#ifndef GXX_INET_SOCKET2_H
#define GXX_INET_SOCKET2_H

namespace gxx {
	class socket {
		socket(int domain, int type, int protocol) {
			sock = ::socket(domain, type, protocol);		
		}
	};
}

#endif