#ifndef GXX_SOCKET_H
#define GXX_SOCKET_H

#include <inttypes.h>
#include <gxx/io/iostream.h>
#include <gxx/inet/hostaddr.h>
#include <gxx/util/setget.h>
#include <gxx/result.h>

//#include <fstream>
/*
using namespace gxx::result_type;

namespace gxx {
	enum class SocketError : uint8_t {
		WrongSocketType,
		ConnectionRefused,
		UnknownError,
		AllreadyInUse,
		Unavailable,
		BrokenPipe,
		OK,
	};

	enum class SocketState : uint8_t {
		Disconnected,
		Connecting,
		Connected,
		Bound,
		
		//Opened,
		Listening,
	};

	class socket : public gxx::io::iostream {
	public:
		enum class type : uint8_t {
			Unix,
			tcp,
			udp,
			rdm,
		};

		static constexpr int32_t AnyAddress = 0; 

		socket(const socket&) = delete;
		socket(socket&&) = default;

		socket& operator= (const socket&) = delete;
		socket& operator= (socket&&) = default;

	protected:
		int m_fd = -1;
		//gxx::string m_errstr;

		hostaddr m_addr;
		uint16_t m_port;

				type m_type;
		SocketError m_error = SocketError::OK;
		SocketState m_state = SocketState::Disconnected;

		void setError(const char* func, int err);
		void setError(const char* func, SocketError err);

	public:
		socket();
		socket(socket::type type, const hostaddr& addr, uint16_t port);

		int open();
		int close();

		void init(socket::type type, const hostaddr& addr, uint16_t port);

		int bind();
		int connect();
		int listen(int maxcon); 
		gxx::socket accept();
		int try_accept(gxx::socket& sock);
		
		int send(const char* data, size_t size, int flags);
		int recv(char* data, size_t size, int flags);
		
		int nodelay(bool en);
		int blocking(bool en);
		int reusing(bool en);

		CONSTREF_GETTER(host, m_addr);
		CONSTREF_GETTER(port, m_port);
		CONSTREF_GETTER(fd, m_fd);
		CONSTREF_GETTER(state, m_state);

		FLOW_SETTER(set_fd, m_fd);
		FLOW_SETTER(set_state, m_state);

		bool is_connected() { return m_state == SocketState::Connected; }
		bool is_disconnected() { return m_state == SocketState::Disconnected; }
		bool is_listening() { return m_state == SocketState::Listening; }
		//bool is_error() { return m_error != SocketState::OK; }

		static gxx::socket from_descriptor(int fd);

	protected:
		int writeData(const char* str, size_t sz) override;		
		int readData(char* str, size_t sz) override;	

	public:
		const char* error() {
			switch(m_error) {
								case SocketError::WrongSocketType: return "WrongSocketType";
				case SocketError::AllreadyInUse: return "AllreadyInUse";
				case SocketError::ConnectionRefused: return "ConnectionRefused";
				case SocketError::Unavailable: return "Unavailable";
				case SocketError::BrokenPipe: return "BrokenPipe";
				case SocketError::OK: return "NotError";				
				default: return "UnknownError";
			}
		}	
	};
}
*/
#endif
