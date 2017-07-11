#ifndef GXX_JSON_PARSER_H
#define GXX_JSON_PARSER_H

//#include <gxx/io/text_readeis.h>
#include <gxx/result.h>
#include <gxx/serialize/json.h>

#include <istream>

using namespace gxx::result_type;

namespace gxx {
	class json_parser {
	public:
		static result<json> parse(std::istream& is);
		static json parse_number(std::istream& is);
		static result<json> parse_string(std::istream& is);
		static result<json> parse_array(std::istream& is);
		static result<json> parse_dictionary(std::istream& is);
	};
}

#endif