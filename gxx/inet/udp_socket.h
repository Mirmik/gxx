#ifndef GXX_DATAGRAMM_SOCKET_H
#define GXX_DATAGRAMM_SOCKET_H

namespace gxx {
	class udp_socket {
		void write_datagramm(const char* data, size_t size);
		gxx::datagramm receive_datagramm();
	};
}

#endif