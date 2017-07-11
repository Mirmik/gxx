#include <gxx/io/file.h>

int main() {

	gxx::unix::File hello("hello");
	hello.open(gxx::IODevice::OpenMode::WriteOnly);
	hello.writeData("33", 2);
	hello.close();

}