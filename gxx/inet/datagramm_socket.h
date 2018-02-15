#ifndef GXX_UDP_SOCKET_H
#define GXX_UDP_SOCKET_H

namespace gxx {
	class datagramm_socket {
		virtual void write_datagramm(const char* data, size_t size);
		virtual void read_datagramm(char* data, size_t size);
	};

	class udp_socket : public datagramm_socket {
		int sock;
	};
}

#endif