#ifndef GXX_IO_RING_STREAM_H
#define GXX_IO_RING_STREAM_H

#include <gxx/io/iostream.h>
#include <gxx/bytering.h>

namespace gxx {
	namespace io {
		class ring_stream : public gxx::io::iostream {
			bytering ring;

		public:
			ring_stream(gxx::buffer buf) : ring(buf) {}

			int writeData(const char* str, size_t sz) override {
				ring.push(str, sz);
			}

			int readData(char* str, size_t sz) override {

			}

			void dump(gxx::io::ostream& out) {
				out.print(ring.first_part_as_buffer());
				out.print(ring.last_part_as_buffer());
			}
		};
	}
}

#endif