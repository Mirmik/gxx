#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <ostream>
#include <gxx/serialize/datatree.h>

namespace gxx {
	class json : public datatree {
	public:
		template<typename ... Args> 
		json(Args ... args) : datatree(std::forward<Args>(args) ...) {}

		void printTo(std::ostream& os);
		void prettyPrintTo(std::ostream& os, int tab = 0);
	};

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