#include <gxx/io/fstream.h>
#include <unistd.h>

int gxx::io::fstream::writeData(const char* str, size_t sz) {
	return ::write(fd, str, sz);
}  
