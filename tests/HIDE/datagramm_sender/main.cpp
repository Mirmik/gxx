#include <gxx/inet/dgramm.h>
#include <gxx/print.h>

int main() {
	gxx::inet::udp_socket udp_sock;
	//gxx::inet::rdm_socket rdm_sock;
	
	const char* str = "HelloAnotherSocket";
	udp_sock.sendto("127.0.0.1", 11001, str, strlen(str));
	//rdm_sock.sendto("127.0.0.1", 11002, str, strlen(str));
}