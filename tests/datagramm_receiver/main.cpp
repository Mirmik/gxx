#include <gxx/inet/dgramm.h>
#include <gxx/print.h>

int main() {
	gxx::inet::udp_socket udp_sock(gxx::inet::localhost, 11001);
	//gxx::inet::rdm_socket rdm_sock(gxx::inet::localhost, 11002);

	char buf[128];
	gxx::inet::netaddr inaddr;
	
	size_t ret;
	while(1) {
		ret = udp_sock.recvfrom(buf, 128, &inaddr);
		gxx::fprintln("udp: {}: {}", inaddr, gxx::buffer(buf, ret));
	
	//	ret = rdm_sock.recvfrom(buf, 128, &inaddr);
	//	gxx::println(ret);
		//gxx::fprintln("rdm: {}: {}", inaddr, gxx::buffer(buf, ret));
	}
}