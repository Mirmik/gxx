#include <gxx/inet/dgramm.h>
#include <gxx/print.h>

int main() {
	char buf[128];

	gxx::inet::udp_socket u1, u2;

	gxx::println("binds");
	u1.bind(11003);
	u2.bind(11004);

	gxx::println("send");
	u1.sendto("127.0.0.1", 11004, "HelloWorld", 10);

	gxx::println();
	//gxx::println(gxx::inet::hostaddr("127.0.0.1"));

	gxx::println("recv");
	
	gxx::inet::netaddr inaddr;
	int size = u2.recvfrom(buf, 128, &inaddr);

	gxx::writeln(buf, size);
}