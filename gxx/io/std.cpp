#include <gxx/io/std.h>

namespace gxx { namespace io {
	gxx::io::std_ostream cout(std::cout.rdbuf());
	gxx::io::std_ostream cerr(std::cerr.rdbuf());
	gxx::io::std_istream cin(std::cin.rdbuf());
}}