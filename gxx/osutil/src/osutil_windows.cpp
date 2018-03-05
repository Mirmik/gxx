#include <fcntl.h>
#include <winsock2.h>
#include <stdio.h>

#include <gxx/osutil/fd.h>

int gxx::osutil::nonblock(int fd, bool en) {
	unsigned long mode = en;
	return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
}
