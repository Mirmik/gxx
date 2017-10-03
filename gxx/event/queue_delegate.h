#ifndef GXX_EVENT_QUEUE_DELEGATE_H
#define GXX_EVENT_QUEUE_DELEGATE_H

#include <gxx/ring.h>
#include <gxx/event/delegate.h>

namespace gxx {
	class queue_delegate {
		gxx::ring<gxx::delegate> ring;
	};
}

#endif