#ifndef GXX_OSUTIL_SIGNAL_H
#define GXX_OSUTIL_SIGNAL_H

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

namespace gxx {
	namespace osutil {
		void setsig(int fd, int sig) {
			fcntl(fd, F_SETOWN, getpid());
			fcntl(fd, F_SETSIG, SIGUSR1);
			fcntl(fd,F_SETFL,fcntl(fd,F_GETFL) | O_NONBLOCK | O_ASYNC); 
   		}

   		void signal(int sig, void(*handler)(int)) {
   			::signal(sig, handler);
   		}
	}
}

#endif