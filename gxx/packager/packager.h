#ifndef GXX_PACKAGER_H
#define GXX_PACKAGER_H

#include <gxx/io/iostorage.h>
#include <gxx/sline.h>
#include <gxx/util/setget.h>
#include <gxx/util/crc.h>
#include <gxx/util/gmsg.h>

namespace gxx {
	class packager {
		gxx::sline line;
		uint8_t crc;
		uint8_t state = 0;
		gxx::delegate<void, gxx::buffer> dlg;
		bool _debug = false;

	private: 

		inline void addchar(char c) {
			line.putchar(c);
			strmcrc8(&crc, c);
		}

	public:
		ACCESSOR(debug_mode, _debug);
		packager(gxx::buffer buf) : line(buf) {}

		void init() {
			crc = 0xFF;
			line.init();
		}

		void invoke_callback() {
			line.back(1);
			dlg(line);
		}

		void set_callback(gxx::delegate<void, gxx::buffer> dlg) {
			this->dlg = dlg;
		}

		void setstate(int n) {
			state = n;
			if (_debug) dprln("packager::setstate", n);
		}

		void newchar(char c) {
			if (_debug) dprln("packager::newchar", c, (int) c);
			switch (state) {
				case 0:
					if (c == gxx::gmsg::strt) {
						init();
						setstate(1);
					}
					break;
				case 1:
					switch (c) {
						case gxx::gmsg::strt:
							if (line.size() == 0) break;
							if (crc != 0) { 
								dprln("packager::crc_error:", crc);\
							}
							else invoke_callback();
							init();
							break;
						case gxx::gmsg::stub:
							setstate(2);
							break;
						default:
							addchar(c);
					}
					break;

				case 2:
					switch (c) {
						case gxx::gmsg::stub_strt:
							addchar(gxx::gmsg::strt);
							setstate(1);
							break;
						case gxx::gmsg::stub_stub:
							addchar(gxx::gmsg::stub);
							setstate(1);
							break;
						default:
							dpr("packager::stub_error: ");
							dprhexln(c);
							setstate(0);
					}				
					break;

			}
		}
	};
}

#endif