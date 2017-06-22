#ifndef GXX_SOCKET_H
#define GXX_SOCKET_H

#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

#include <gxx/debug/dprint.h>
#include <gxx/io2/strm.h>


namespace gxx {
	namespace io {
		class socket_strmio;
	}

	class socket {
	protected:
		int32_t ip;
		int port;
		
		int sock;
		sockaddr_in addr;
		
	public:
		socket(int32_t ip, int port) : ip(htonl(ip)), port(port) {}

		int open() {
			addr.sin_family = AF_INET;
	    	addr.sin_port = htons(port);
   		 	addr.sin_addr.s_addr = ip;

   		 	sock = ::socket(PF_INET, SOCK_STREAM, 0);
   			if (sock < 0) {
   				return -1;
   				//abort_dprln("socket::cant create socket");
   			}

   			return 0;
		}

		int bind() {
			return ::bind(sock, (struct sockaddr*) &addr, sizeof(addr));
		}

    	int listen(int con) {
			return ::listen(sock, con);
    	}

    	bool blocking(bool en)
		{
		   if (sock < 0) return false;
		   int flags = fcntl(sock, F_GETFL, 0);
		   if (flags < 0) return false;
		   flags = en ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
		   return (fcntl(sock, F_SETFL, flags) == 0) ? true : false;
		}

		gxx::io::socket_strmio as_stream();
	};

	class socket_strmio : public gxx::io::strmio {

	};
}

#endif