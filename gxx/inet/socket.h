#ifndef GXX_SOCKET_H
#define GXX_SOCKET_H

#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>

#include <gxx/debug/dprint.h>
#include <gxx/io/strm.h>
#include <gxx/io/text_reader.h>


namespace gxx {
	namespace io {
		class socket_strmio;
	}

	class socket : public gxx::io::strmio {
	protected:
		int fd;
		sockaddr_in addr;

		gxx::string m_errstr;
		
	public:
		socket() {}

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

		int open() {
			fd = ::socket(PF_INET, SOCK_STREAM, 0);
   			if (fd < 0) {
   				m_errstr = strerror(errno);
   				return -1;
   			}

   			return 0;
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
	};

}

#endif