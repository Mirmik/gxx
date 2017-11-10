#ifndef GXX_PACKAGER_OPACKAGER_H
#define GXX_PACKAGER_OPACKAGER_H

#include <gxx/io/ostream.h>
#include <gxx/util/crc.h>
#include <gxx/util/gmsg.h>

namespace gxx {
	class opackager {
		gxx::io::ostream& out;
		uint8_t crc = 0xFF;

	public:
		opackager(gxx::io::ostream& out) : out(out) {}

		void prefix() {
			out.putchar(gxx::gmsg::strt);
			crc = 0xFF;
		}

		void postfix() {
			out.putchar(crc);			
			out.putchar(gxx::gmsg::strt);
			crc = 0xFF;
		}

		void part(const char* data, size_t size) {
			const char* end = data + size;
			for(; data != end; data++) {
				part(*data);
			}
		}

		void part(gxx::buffer buf) {
			part(buf.data(), buf.size());
		}

		void part(char c) {
			strmcrc8(&crc, c);
			switch (c) {
				case (char)gxx::gmsg::strt: 
					out.putchar(gxx::gmsg::stub); 
					out.putchar(gxx::gmsg::stub_strt); 
					break;
		
				case (char)gxx::gmsg::stub: 
					out.putchar(gxx::gmsg::stub); 
					out.putchar(gxx::gmsg::stub_stub); 
					break;
		
				default:
					out.putchar(c);
					break;
			}
		}

	};
}

#endif