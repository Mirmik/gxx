#ifndef GXX_IO_RING_STREAM_H
#define GXX_IO_RING_STREAM_H

#include <gxx/event/once_delegate.h>
#include <gxx/io/iobuffer.h>
#include <gxx/bytering.h>

namespace gxx {
	namespace io {
		class ringbuffer : public gxx::io::iobuffer {
			bytering ring;

			gxx::once_delegate<void> emptydlg;
			gxx::once_delegate<void> availdlg;

		public:
			ringbuffer(gxx::buffer buf) : ring(buf) {}

			int avail() override { return ring.avail(); }
			int room() override { return ring.room(); }

			int writeData(const char* str, size_t sz) override {
				ring.push(str, sz);
				availdlg();
			}

			int readData(char* str, size_t sz) override {
				if (ring.empty()) emptydlg();
			}

			void dump(gxx::io::ostream& out) {
				out.print(ring.first_part_as_buffer());
				out.print(ring.last_part_as_buffer());
			}

			void dump(gxx::io::ostream&& out) { dump(out); }

			void retrans(gxx::io::ostream& out) {
				out.print(ring.first_part_as_buffer());
				out.print(ring.last_part_as_buffer());
				ring.clean();
			}

			void retrans(gxx::io::ostream&& out) { retrans(out); }

			void empty_callback(gxx::action dlg) override {
				emptydlg = dlg;
			}

			void avail_callback(gxx::action dlg) override {
				availdlg = dlg;
			}

		};
	}
}

#endif