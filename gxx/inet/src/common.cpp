#include <unistd.h>
#include <fcntl.h>

//#ifdef _WIN32
//#	include <winsock2.h>
//#	include <ws2tcpip.h>
//#else
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
//#endif

#include <errno.h>

#include <gxx/inet/hostaddr.h>
#include <gxx/inet/tcp_socket.h>
#include <gxx/inet/tcp_server.h>
#include <gxx/inet/dgramm.h>

#include <gxx/warnings.h>

#include <gxx/osutil/fd.h>

/*#if defined(__WIN32__) || defined(__WIN64__)
using sa_family_t = int;
#endif*/

__attribute__((deprecated))
int gxx::inet::socket::blocking(bool en)
{
	return gxx::osutil::nonblock(fd, !en);
}

int gxx::inet::socket::nonblock(bool en)
{
	int ret = gxx::osutil::nonblock(fd, en);
	if (GXX_WARNINGS && ret < 0) {
		perror("warn: socket::nodelay");
	}

	return ret;
}

int gxx::inet::socket::nodelay(bool en)
{
	int on = en;
	int rc = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof(on));
	if (GXX_WARNINGS && rc < 0) {
		perror("warn: socket::nodelay");
	}
	return rc;
}

int gxx::inet::socket::reusing(bool en)
{
	int on = en;
	int rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof (on));
	if (GXX_WARNINGS && rc < 0) {
		perror("warn: socket::reusing");
	}
	return rc;
}

int gxx::inet::socket::init(int domain, int type, int proto)
{
	fd = ::socket(domain, type, proto);
	if (GXX_WARNINGS && fd < 0) {
		perror("warn: socket::init");
	}

	return fd;
}

int gxx::inet::socket::bind(const gxx::inet::hostaddr& haddr, uint16_t port, int family)
{
	int sts;
	struct sockaddr_in addr;
	
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = (sa_family_t)family;
	addr.sin_addr.s_addr = htonl(haddr.addr);  //INADDR_ANY = 0.0.0.0
	addr.sin_port = htons(port);

	sts = ::bind(fd, (sockaddr*) &addr, sizeof(struct sockaddr_in));
	if (GXX_WARNINGS && sts < 0) {
		perror("warn: socket::bind");
	}

	return sts;
}

int gxx::inet::socket::listen(int conn)
{
	int sts;
	
	sts = ::listen(fd, conn);
	if (GXX_WARNINGS && sts < 0) {
		perror("warn: socket::listen");
	}

	return sts;
}

int gxx::inet::socket::connect(const gxx::inet::hostaddr& haddr, uint16_t port, int family)
{
	int sts;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = (sa_family_t)family;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(haddr.addr);

	sts = ::connect(fd, (struct sockaddr*) &addr, sizeof(addr));
	if (GXX_WARNINGS && sts < 0) {
		perror("warn: socket::connect");
	} 

	return sts;
}

int gxx::inet::socket::close()
{
	int sts;

	sts = ::shutdown(fd, SHUT_RDWR);
	if (GXX_WARNINGS && sts < 0) {
		perror("warn: socket::shutdown");
	} 

	sts = ::close(fd);
	if (GXX_WARNINGS && sts < 0) {
		perror("warn: socket::close");
	} 

	return sts;
}


gxx::inet::tcp_socket::tcp_socket(gxx::inet::hostaddr addr, uint16_t port) : tcp_socket()
{
	inet::socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(addr, port);
}

int gxx::inet::tcp_socket::init()
{
	return inet::socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int gxx::inet::tcp_socket::connect(gxx::inet::hostaddr addr, uint16_t port)
{
	return socket::connect(addr, port, PF_INET);
}

ssize_t gxx::inet::tcp_socket::writeData(const char* data, size_t size)
{
	return socket::send(data, size, 0);
}

ssize_t gxx::inet::tcp_socket::readData(char* data, size_t size)
{
	return socket::recv(data, size, 0);
}

ssize_t gxx::inet::socket::send(const char* data, size_t size, int flags)
{
	return ::send(fd, data, size, flags);
}

ssize_t gxx::inet::socket::recv(char* data, size_t size, int flags)
{
	return ::recv(fd, data, size, flags);
}

gxx::inet::tcp_server::tcp_server(const gxx::inet::hostaddr& addr, uint16_t port, int conn)
{
	this->init();
	this->bind(addr, port);
	this->listen(conn);
}

int gxx::inet::tcp_server::init()
{
	return socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int gxx::inet::tcp_server::bind(const gxx::hostaddr& addr, uint16_t port)
{
	return socket::bind(addr, port, PF_INET);
}

int gxx::inet::tcp_server::listen(int conn)
{
	return inet::socket::listen(conn);
}

int gxx::inet::tcp_server::listen()
{
	return inet::socket::listen(10);
}

gxx::inet::tcp_socket gxx::inet::tcp_server::accept()
{
	int c = sizeof(sockaddr_in);
	sockaddr_in caddr;
	memset(&caddr, 0, sizeof(caddr));
	int cfd = ::accept( fd, (sockaddr*)&caddr, (socklen_t*)&c );

	gxx::inet::tcp_socket sock;
	sock.fd = cfd;
	return sock;
}


gxx::inet::datagramm_socket::datagramm_socket(int domain, int type, int proto)
{
	socket::init(domain, type, proto);
}

ssize_t gxx::inet::datagramm_socket::sendto(gxx::inet::hostaddr haddr, uint16_t port, const char* data, size_t size)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = htonl(haddr.addr);  //INADDR_ANY = 0.0.0.0
	addr.sin_port = htons(port);

	return ::sendto(fd, data, size, 0, (sockaddr*) &addr, sizeof(sockaddr_in));
}

ssize_t gxx::inet::datagramm_socket::ne_sendto(uint32_t ipaddr, uint16_t port, const char* data, size_t size)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = ipaddr;  //INADDR_ANY = 0.0.0.0
	addr.sin_port = port;

	return ::sendto(fd, data, size, 0, (sockaddr*) &addr, sizeof(sockaddr_in));
}

ssize_t gxx::inet::datagramm_socket::recvfrom(char* data, size_t maxsize, gxx::inet::netaddr* inaddr)
{
	struct sockaddr_in si_other;
	socklen_t sz = sizeof(sockaddr_in);
	ssize_t ret = ::recvfrom(fd, data, maxsize, 0, (sockaddr*) &si_other, &sz);

	if (ret < 0) {
		return ret;
		//gxx::println(strerror(errno));
	}

	if (inaddr) *inaddr = gxx::inet::netaddr(ntohl(si_other.sin_addr.s_addr), ntohs(si_other.sin_port));
	return ret;
}

gxx::inet::udp_socket::udp_socket() : datagramm_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) {}

gxx::inet::udp_socket::udp_socket(gxx::inet::hostaddr addr, uint16_t port) : udp_socket()
{
	bind(addr, port);
}

int gxx::inet::udp_socket::bind(gxx::inet::hostaddr addr, uint16_t port)
{
	return socket::bind(addr, port, PF_INET);
}

gxx::inet::rdm_socket::rdm_socket() : datagramm_socket(AF_INET, SOCK_RDM, 0) {}

gxx::inet::rdm_socket::rdm_socket(gxx::inet::hostaddr addr, uint16_t port) : rdm_socket()
{
	socket::bind(addr, port, PF_INET);
}
