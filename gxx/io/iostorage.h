#ifndef GXX_IO_OBUFFER_H
#define GXX_IO_OBUFFER_H

#include <gxx/io/iostream.h>
#include <gxx/event/delegate.h>

namespace gxx {
	namespace io {
		/*class obuffer : public gxx::io::ostream {
		public:
			virtual int room() = 0;
			virtual void empty_callback(gxx::action dlg) {};
		};*/

		class istorage : public gxx::io::istream {
		public:
			virtual int avail() = 0;
			virtual void set_avail_callback(gxx::action dlg) {};
		};

		//class iobuffer : public gxx::io::obuffer, public gxx::io::ibuffer {}; 
	}
}

#endif