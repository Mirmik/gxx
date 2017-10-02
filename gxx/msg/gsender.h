#ifndef GXX_GSENDER_H
#define GXX_GSENDER_H

#include <gxx/vecbuf.h>
#include <gxx/msg/sender.h>
#include <gxx/util/crc.h>

namespace gxx {
	namespace msg {
		namespace gmsgproto {
			class sender {
			public:
				gxx::io::ostream* out;
				sender(gxx::io::ostream* out) : out(out) {}

				uint8_t crc;

				/*void start() override {
					crc = 0xFF;
					out->putchar(0xFF);
				}

				void part(gxx::buffer buf) override {
					auto end = buf.data() + buf.size();
					for (auto ptr = buf.data(); ptr != end; ptr++) {
						strmcrc8(&crc, *ptr);
					}
					out->write(buf.data(), buf.size());
				}

				void finish() override {
					out->putchar(crc);
				}*/

				void send(const gxx::vecbuf& vec) {
					uint8_t crc = 0xFF;
					int16_t len = 0;
					for (const auto& v : vec) {
						len += v.size();
					}

					out->fill('\0', 3);
					out->write((char*)&len, 2);

					for (const auto& v : vec) {
						auto pend = v.data() + v.size();
						for (auto ptr = v.data(); ptr != pend; ++ptr) 
							strmcrc8(&crc, *ptr);
						out->print(v);
					}

					out->putchar(crc);
				}			
			};

			class receiver {
				gxx::line_buffer buf;

			};
		}
	}
}

#endif