#ifndef GXX_SOCKET_SERVER_H
#define GXX_SOCKET_SERVER_H

#include <gxx/inet/socket.h>

namespace gxx {
	class server : public socket {
	public:

		server(int port) : socket(INADDR_ANY, port) {

		}

		int accept(gxx::socket* client) {
			int c = sizeof(sockaddr_in);
			sockaddr_in caddr;
			memset(&caddr, 0, sizeof(caddr));

			int cfd = ::accept( fd, (sockaddr*)&caddr, (socklen_t*)&c );
			if (cfd < 1) {
				m_errstr = strerror(errno);
				return -1;
			}

			client->init(caddr.sin_addr.s_addr, caddr.sin_port, caddr.sin_family); 
			client->setFileDescriptor(cfd);
			return 0;
		}

		int start(int con, bool reuse = false) {
			if (open() < 0) return -1;

			if (reuse) reusing(reuse);

			if (bind() < 0) return -1;
			if (listen(con) < 0) return -1;
			return 0;
		}


	};
}

#endif