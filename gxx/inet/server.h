#ifndef GXX_SOCKET_SERVER_H
#define GXX_SOCKET_SERVER_H

#include <gxx/inet/socket.h>

namespace gxx {
	class server : public socket {
	public:

		server(int port) : socket(INADDR_ANY, port) {

		}

		int accept() {
			int c;
			sockaddr_in client_addr;
			return ::accept( sock, (sockaddr*)&client_addr, (socklen_t*)&c );
		}

		void start(int con) {
			open();
			bind();
			listen(con);
		}


	};
}

#endif