#ifndef OSTREAM_MESSENGER_H
#define OSTREAM_MESSENGER_H

#include <gxx/io/ostream.h>
#include <gxx/util/crc.h>

namespace gxx {
    namespace io {
        class ostream_messenger : public gxx::io::ostream {
            virtual void start_message() = 0;
            virtual void end_message() = 0;
        };

        class gmessenger : public ostream_messenger {
            gxx::io::ostream& out;
            uint8_t crc;

            constexpr static uint8_t strt = 0xDC;
            constexpr static uint8_t stub = 0xDD;
            constexpr static uint8_t stub_strt = 0xDE;
            constexpr static uint8_t stub_stub = 0xDF;

        public:
            gmessenger(gxx::io::ostream& out) : out(out) {}

            void start_message() override {
                out.putchar(strt);
                crc = 0xFF;
            }

            void end_message() override {
                out.putchar(crc);
                out.putchar(strt);
            }

        protected:
            int writeData(const char* str, size_t sz) override {
                while(sz--) {
                    uint8_t c = *str++;
                    strmcrc8(&crc, c);
                    switch(c) {
                        case strt:
                            out.putchar(stub);
                            out.putchar(stub_strt);

                        case stub:
                            out.putchar(stub);
                            out.putchar(stub_stub);

                        default:
                            out.putchar(c);
                    }
                }
            }
        };
    }
}

#endif // OSTREAM_MESSENGER_H
