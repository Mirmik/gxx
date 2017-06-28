#include <gxx/inet/socket.h>

namespace gxx {

	gxx::socket socket::from_descriptor(int fd) {
		return gxx::move(gxx::socket().set_fd(fd));
	}

	void socket::init(SocketType type, const hostaddr& addr, uint16_t port) {
		m_addr = addr;
		m_port = port;
		m_type = type;
	}

	socket::socket() {}
	
	socket::socket(SocketType type, const hostaddr& addr, uint16_t port) {
		init(type, addr, port);
	}


}