#ifndef GXX_SOCKET_H
#define GXX_SOCKET_H

#include <gxx/io/strm.h>
#include <gxx/inet/hostaddr.h>

#include <gxx/util/setget.h>

namespace gxx {
	enum class SocketType : uint8_t {
		Tcp,
		Udp,
		Unix,
	};

	enum class SocketError : uint8_t {
		ConnectionRefused,
		UnknownError,
		OK,
	};

	enum class SocketState : uint8_t {
		NoInit,
		Opened,
	};

	class socket : public gxx::io::strmio {
	protected:
		int m_fd = -1;
		//gxx::string m_errstr;

		hostaddr m_addr;
		uint16_t m_port;

		SocketType m_type;
		SocketError m_error = SocketError::OK;
		SocketState m_state = SocketState::NoInit;

	public:
		socket() {}
		socket(const hostaddr& addr, uint16_t port, SocketType type = SocketType::Tcp) {
			init(addr, port, type);
		}

		int open();
		void init(const hostaddr& addr, uint16_t port, SocketType type = SocketType::Tcp);

		int connect();

		CONSTREF_GETTER(host, m_addr);
		CONSTREF_GETTER(port, m_port);

	private:
		int writeData(const char* str, size_t sz) override;		
		int readData(char* str, size_t sz) override;	

	public:
		const char* error() {
			switch(m_error) {
				case SocketError::ConnectionRefused: return "ConnectionRefused";
				case SocketError::OK: return "NotError";
				default: return "UnknownError";
			}
		}	
	};
}

#endif