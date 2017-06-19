#ifndef GXX_IOC_IOCHANNEL_H
#define GXX_IOC_IOCHANNEL_H

namespace gxx {
	class ichannel {
		virtual int read(char* buf, size_t maxLen);
		virtual int readsome(char* buf, size_t maxLen);

	}
}

#endif