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
		AllreadyInUse,
		OK,
	};

	enum class SocketState : uint8_t {
		Disconnected,
		Connecting,
		Connected,
		Bound,
		
		Opened,
		Listening,
	};

	class socket : public gxx::io::strmio {
	public: 
		static constexpr int32_t AnyAddress = 0; 

		socket(const socket&) = delete;
		
		socket(socket&&) = default;

	protected:
		int m_fd = -1;
		//gxx::string m_errstr;

		hostaddr m_addr;
		uint16_t m_port;

		SocketType m_type;
		SocketError m_error = SocketError::OK;
		SocketState m_state = SocketState::Disconnected;

	public:
		socket() {}
		socket(const hostaddr& addr, uint16_t port, SocketType type = SocketType::Tcp) {
			init(addr, port, type);
			open();
		}

		int open();
		void init(const hostaddr& addr, uint16_t port, SocketType type = SocketType::Tcp);

		int bind();
		int connect();
		int listen(int maxcon);
		gxx::socket accept();

		int blocking(bool en);
		int reusing(bool en);

		CONSTREF_GETTER(host, m_addr);
		CONSTREF_GETTER(port, m_port);
		CONSTREF_GETTER(fd, m_fd);
		CONSTREF_GETTER(state, m_state);

		//SETTER(set_fd, m_fd);
		//SETTER(set_state, m_state);

		bool is_connected() { return m_state == SocketState::Connected; }

	private:
		int writeData(const char* str, size_t sz) override;		
		int readData(char* str, size_t sz) override;	

	public:
		const char* error() {
			switch(m_error) {
				case SocketError::AllreadyInUse: return "AllreadyInUse";
				case SocketError::ConnectionRefused: return "ConnectionRefused";
				case SocketError::OK: return "NotError";				
				default: return "UnknownError";
			}
		}	
	};
}

#endif