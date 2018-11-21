#include <gxx/util/text.h>
#include <gxx/print.h>

int main() {
	gxx::println("bright:");
	gxx::println(gxx::text::black("\tblack"));
	gxx::println(gxx::text::red("\tred"));
	gxx::println(gxx::text::green("\tgreen"));
	gxx::println(gxx::text::yellow("\tyellow"));
	gxx::println(gxx::text::blue("\tblue"));
	gxx::println(gxx::text::magenta("\tmagenta"));
	gxx::println(gxx::text::cyan("\tcyan"));
	gxx::println(gxx::text::white("\twhite"));

	gxx::println();
	gxx::println("dark:");
	gxx::println(gxx::text::bright_black("\tbright_black"));
	gxx::println(gxx::text::bright_red("\tbright_red"));
	gxx::println(gxx::text::bright_green("\tbright_green"));
	gxx::println(gxx::text::bright_yellow("\tbright_yellow"));
	gxx::println(gxx::text::bright_blue("\tbright_blue"));
	gxx::println(gxx::text::bright_magenta("\tbright_magenta"));
	gxx::println(gxx::text::bright_cyan("\tbright_cyan"));
	gxx::println(gxx::text::bright_white("\tbright_white"));
}