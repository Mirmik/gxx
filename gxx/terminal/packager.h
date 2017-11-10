#ifndef GXX_PACKAGER_H
#define GXX_PACKAGER_H

#include <gxx/io/iostorage.h>
#include <gxx/sline.h>
#include <gxx/util/crc.h>
#include <gxx/util/gmsg.h>

namespace gxx {
	class packager {
		gxx::sline line;
		uint8_t crc;
		uint8_t state = 0;
		gxx::delegate<void, gxx::buffer> dlg;

	public:
		packager(gxx::buffer buf) : line(buf) {}

		void init() {
			crc = 0xFF;
			line.init();
		}

		void invoke_callback() {
			dlg(line);
		}

		void newchar(char c) {
			dpr("symb", c);
			switch (state) {
				case 0:
					if (c == gxx::gmsg::strt) {
						init();
						state = 1; 
					}
					break;
				case 1:
					switch (c) {
						case gxx::gmsg::stub:
							state = 2;
							break;
						case gxx::gmsg::strt:
							if (crc != 0) dprln("packager::crc_error:", crc);
							else invoke_callback();
							init();
							break;
						default:
							line.putchar(c);
							strmcrc8(&crc, c);
							break;
					}
					break;

				case 2:
					break;

			}
		}
	};
}

#endif