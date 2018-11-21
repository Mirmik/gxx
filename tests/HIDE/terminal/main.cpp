#include <gxx/terminal/terminal.h>
#include <gxx/debug/debug_ostream.h>

gxx::debug_ostream dout;
gxx::terminal_core terminal(dout);

int main() {
	terminal.start();
	terminal.newchar('m');
	terminal.newchar('i');
	terminal.newchar('r');
	terminal.newchar('m');
	terminal.newchar('i');
	terminal.newchar('k');

	terminal.newchar(0x28);
	terminal.newchar('[');
	terminal.newchar('1');
	terminal.newchar('D');

	dprln();
}