#include <gxx/io/unixfile.h>

int main() {
	gxx::io::ufile f("test.dat");
	f.open(gxx::io::WriteOnly | gxx::io::Truncate);

	f.println("HelloWorld");
	f.println("HelloWorld");
	f.println("HelloWorld {}", 980);
	f.close();
}