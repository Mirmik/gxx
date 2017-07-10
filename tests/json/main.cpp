//#include <gxx/string.h>
#include <gxx/serialize/json.h>

/*#include <gxx/serialize/json_parser.h>
#include <gxx/io/memory_stream.h>
#include <gxx/io/text_writer.h>
#include <gxx/buffer.h>*/
//#include <sstream>

/*using namespace gxx::string_literal;
using namespace gxx::buffer_literal;

auto dos = gxx::debug_ostream();*/

int main() {
	/*const char* str = R"(      { "kekeke": {"mir" : 987 } }  ggg    )";

	gxx::memory_stream is = gxx::memory_stream(gxx::buffer(str));
	gxx::json js = gxx::json_parser::parse(gxx::text_reader(is)).unwrap();
	js.printTo(gxx::text_writer(dos));dln();*/

	gxx::json js = std::string("lalala");
}