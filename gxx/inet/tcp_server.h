#ifndef GXX_INET_TCP_SERVER_H
#define GXX_INET_TCP_SERVER_H

#include <gxx/inet/tcp_socket.h>


namespace gxx {
	namespace inet {
		struct tcp_server : public inet::socket {
			tcp_server() = default;
			
                        tcp_server(int port);
                        tcp_server(gxx::inet::hostaddr addr, int port);
                        void listen(int port, int conn = 10);
                        inet::tcp_socket accept();
		};
	}
}

#endif
