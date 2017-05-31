#include <iostream>
#include <gxx/inet/spam_server.h>

int main() {

	gxx::spam_server spam(9876);
	spam.start(10);

	while(1) {
		spam.send("hello\r\n", 7);
	}
}