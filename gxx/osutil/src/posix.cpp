#include <fcntl.h>
#include <gxx/osutil/fd.h>

int gxx::osutil::nonblock(int fd, bool en) {
   if (fd < 0) return -1;
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags < 0) return -1;
   flags = en ? (flags|O_NONBLOCK) : (flags&~O_NONBLOCK);
   return fcntl(fd, F_SETFL, flags) == 0;
}

/*int gxx::osutil::nodelay(int fd, bool en) {
	int on = en;
	int rc = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof(on));
	return rc;
}*/