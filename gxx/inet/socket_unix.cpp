#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>

#include <gxx/inet/socket.h>

namespace gxx {
	void socket::init(const hostaddr& addr, uint16_t port, SocketType type) {
		m_addr = addr;
		m_port = port;
		m_type = type;
	}

	int socket::open() {
		switch(m_type) {
			case SocketType::Tcp: 
				m_fd = ::socket(PF_INET, SOCK_STREAM, 0);
				break;
			default:
				m_error = SocketError::UnknownError;
				return -1;	
		}
		
		if (m_fd < 0) {
			m_error = SocketError::UnknownError;
			return -1;
		}
	
		m_state = SocketState::Opened;
		return 0;
	}
	
	int socket::connect() {
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));

		switch(m_type) {
			case 
				SocketType::Tcp: addr.sin_family = AF_INET;
				break;
			default:
				switch(errno) {
					case ECONNREFUSED: m_error = SocketError::ConnectionRefused; break;
					default: 
						dprln(errno);
						perror("debug");
				} 
		}

		addr.sin_port = htons(m_port);
   	 	addr.sin_addr.s_addr = htonl(m_addr.addr);

		if (::connect(m_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
			switch(errno) {
				case ECONNREFUSED: m_error = SocketError::ConnectionRefused; break;
				default: 
					dprln(errno);
					perror("debug");
			}			
			return -1;				
		}

		m_state = SocketState::Connected;		
		return 0;			 
	}

	int socket::listen(int con) {
		if (::listen(m_fd, con) < 0) {
   			switch(errno) {
				case ECONNREFUSED: m_error = SocketError::ConnectionRefused; break;
				default: 
					dprln(errno);
					perror("debug");
					return -1;
			}					
			return -1;
		}

		m_state = SocketState::Listening;
		return 0;		
    }

	int socket::bind() {
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		
		addr.sin_port = htons(m_port);
   	 	addr.sin_addr.s_addr = htonl(m_addr.addr);

		if (::bind(m_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
   			switch(errno) {
				case EADDRINUSE: m_error = SocketError::AllreadyInUse; break;
				case ECONNREFUSED: m_error = SocketError::ConnectionRefused; break;
				default: 
					dprln(errno);
					perror("debug");
					return -1;
			}					
			m_state = SocketState::Disconnected;
			return -1;
		}

		m_state = SocketState::Bound;
		return 0;			 
	}

    int socket::blocking(bool en)
	{
	   if (m_fd < 0) return -1;
	   int flags = fcntl(m_fd, F_GETFL, 0);
	   if (flags < 0) return -1;
	   flags = en ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
	   return fcntl(m_fd, F_SETFL, flags) == 0;
	}

	int socket::reusing(bool en) {
		int on = en;
		int rc = setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof (on));
		return rc;
	}

	gxx::socket socket::accept() {
		int c = sizeof(sockaddr_in);
		sockaddr_in caddr;
		memset(&caddr, 0, sizeof(caddr));

		int cfd = ::accept( m_fd, (sockaddr*)&caddr, (socklen_t*)&c );
		if (cfd < 1) {
			switch(errno) {
				case EADDRINUSE: m_error = SocketError::AllreadyInUse; break;
				default: 
					dprln(errno);
					perror("debug");
					return gxx::socket();
			}	
		}

		gxx::socket ret;
		ret.init(caddr.sin_addr.s_addr, caddr.sin_port);
		ret.m_fd = cfd;
		ret.m_state = SocketState::Connected;
		//client->init(caddr.sin_addr.s_addr, caddr.sin_port, caddr.sin_family); 
		//client->setFileDescriptor(cfd);
		return gxx::move(ret);
	}

}

/*
	socket(int32_t ip, int port, uint8_t family = AF_INET) {
		init(ip,port,family);
	}

	void init(int32_t ip, int port, uint8_t family = AF_INET) {
		addr.sin_family = family;
		addr.sin_port = htons(port);
   	 	addr.sin_addr.s_addr = htonl(ip);	
	}

	void init(const char* ip, int port, uint8_t family = AF_INET) {
		addr.sin_family = family;
		addr.sin_port = htons(port);
   	 	addr.sin_addr.s_addr = inet_addr(ip);	
	}

	int connect(int32_t ip, int port, uint8_t family = AF_INET) {
		init(ip, port, family);
		if (open()) return -1;
		return connect();
	}

	int connect(const char* ip, int port, uint8_t family = AF_INET) {
		init(ip, port, family);
		if (open()) return -1;
		return connect();
	}

	

	int disconnect() {
		int ret = ::shutdown(fd, SHUT_RDWR);
		if (ret < 0) {
   			m_errstr = strerror(errno);
   			return -1;
   		}

		ret = ::close(fd);
		if (ret < 0) {
   			m_errstr = strerror(errno);
   			return -1;
   		}
   		
   		return 0;
	}

	int bind() {
		if (::bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
   			m_errstr = strerror(errno);
   			return -1;				
		}
		return 0;			 
	}

	int connect() {
		if (::connect(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
   			m_errstr = strerror(errno);
   			return -1;				
		}
		
		return 0;			 
	}

    int listen(int con) {
		if (::listen(fd, con) < 0) {
   			m_errstr = strerror(errno);
   			return -1;				
		}
		return 0;		
    }

    int send(const char* data, size_t size, int flags) {
    	int ret = ::send(fd, data, size, flags | MSG_NOSIGNAL);	
    	if (ret < 0) {
    		m_errstr = strerror(errno);
   			return -1;				
		}
		return ret;	
    }

    int recv(char* data, size_t size, int flags) {
    	int ret = ::recv(fd, data, size, flags | MSG_NOSIGNAL);	
    	if (ret < 0) {
    		m_errstr = strerror(errno);
   			return -1;				
		}
		return ret;	
    }

    int write(const char* data, size_t size) {
    	return send(data, size, 0);
    }

    int read(char* data, size_t size) {
    	return recv(data, size, 0);
    }

    bool blocking(bool en)
	{
	   if (fd < 0) return false;
	   int flags = fcntl(fd, F_GETFL, 0);
	   if (flags < 0) return false;
	   flags = en ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
	   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
	}

	int reusing(bool en) {
		int on = en;
		int rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof (on));
		return rc;
	}

	int nodelay(bool en) {
		int on = en;
		int rc = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof (on));
		return rc;
	}

	gxx::io::text_stream_reader as_text_reader() {
		return gxx::io::text_stream_reader(*this);
	}

	void setFileDescriptor(int newfd) {
		fd = newfd;
	}

	int32_t ip() { return addr.sin_addr.s_addr; }
	int32_t port() { return addr.sin_port; }
	int32_t family() { return addr.sin_family; }

	const gxx::string& errorString() { return m_errstr; }
	
	void clean_input() {
		char buf[128];
		while(int ret = recv(buf, 128, MSG_DONTWAIT) >= 0) {}
	}
*/