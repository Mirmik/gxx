#ifndef GXX_IO_PRINTABLE_H
#define GXX_IO_PRINTABLE_H

#include <gxx/buffer.h>
#include <gxx/debug/dprint.h>

namespace gxx {
	namespace io {
		//class ostream;
		class printable {
		public:
			virtual size_t printTo(gxx::io::ostream& o) const = 0;
		//	virtual size_t fmtPrintTo(gxx::io::ostream& o, gxx::buffer opts) {
		//		return printTo(o);
		//	}
		};
	}
}

#endif