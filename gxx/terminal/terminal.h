#ifndef GXX_TERMINAL_H
#define GXX_TERMINAL_H

#include <gxx/debug/dprint.h>
#include <gxx/io/iostream.h>
#include <gxx/panic.h>
#include <gxx/line.h>

namespace gxx {
	class terminal {
		gxx::io::ostream& out;
		gxx::line line;

	public:
		terminal(gxx::io::ostream & out) : out(out) {}

		uint8_t state = 0;
		uint8_t echo = true;

		int arg = 0;

		void newline() {

		}

		void start() {
			out.print("input> ");
		}

		void left() {}
		void right() {}
		void up() {}
		void down() {}

		void newchar(char c) {
			switch (state) {
				case 0: 
					switch(c) {
						case '\r': 
							return;
						case '\n': 
							newline();
							return;
						case 0x28:
							state = 1;
							return;						
						default:
							if (line.putchar(c)) out.putchar(c);
							return;
					}
				case 1:
					if (c == '[') {
						arg = 0;
						state = 2;
					}
					else state = 0;
					break;
				case 2:
					if (isdigit(c)) { 
						arg = arg * 10 + (c - '0');
						return;
					}
					switch (c) {
						case 'A' : up(); break;
						case 'B' : down(); break;
						case 'C' : left(); break;
						case 'D' : right(); break;
					}
					state = 0;
					break;

				default:
					gxx::panic("terminal, default state");
			}
		}
	};
}

#endif