#include <gxx/inet/dgramm.h>

int main() {
	char buf[128];

	gxx::inet::udp_socket u1, u2;
	u1.bind(11003);
	u2.bind(11004);

	u1.sendto("127.0.0.1", 11004, "HelloWorld", 10);
	u2.recvfrom(buf, 128);
}