#ifndef GXX_OSUTIL_FDOPS_H
#define GXX_OSUTIL_FDOPS_H

namespace gxx {
	namespace osutil {
		int nonblock(int fd, bool en);
		int nodelay(int fd, bool en);
	}
}

#endif