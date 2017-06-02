#ifndef GXX_JSON_PARSER_H
#define GXX_JSON_PARSER_H

#include <gxx/io/text_reader.h>
#include <gxx/result.h>
#include <gxx/serialize/json.h>
using namespace gxx::result_type;

namespace gxx {
	class json_parser {
	public:
		static result<json> parse(const text_reader& r) {
		//	dprln("parse");
			r.ignore_while(isspace);

			char c = r.peek();
			
			if (isdigit(c)) return parse_number(r);
			if (c == '"') return parse_string(r);
			if (c == '[') return parse_array(r);
			if (c == '{') return parse_dictionary(r);

			return json();
		}

		static json parse_number(const text_reader& r) {
		//	dprln("parse_number");
			int ret = r.read_int_decimal();
			return json(ret);
		}

		static result<json> parse_string(const text_reader& r) {
		//	dprln("parse_string");
			r.ignore();
			json ret(r.read_string_until('"'));
			r.ignore();
			return ret;
		}

		static result<json> parse_array(const text_reader& r) {
		//	dprln("parse_array");
		}

		static result<json> parse_dictionary(const text_reader& r) {
			char c;
			json js(json::Type::Dictionary);
			
			while(true) {
				c = r.peek();
				
				if (c == '}') {
					r.ignore();
					return js;
				}				
				
				if (c == ',' || c == '{') {
					r.ignore();
					r.ignore_while(isspace);
				
					c = r.peek();
					if (c == '}') {
						r.ignore();
						return js;
					}				

					if ( c != '"' ) return error("wrong dicionary syntax: not find \"");
					r.ignore();
					gxx::string key = r.read_string_until('"');
					r.ignore();
					
					r.ignore_while(isspace);
					if ( r.peek() != ':' ) return error("wrong dicionary syntax: not find colomn");
					r.ignore();

					r.ignore_while(isspace);
					js.as_dictionary().unwrap().insert(std::make_pair(key, tryS(parse(r))));
					r.ignore_while(isspace);
				}
				else return error("json::internal:dict_parse");
			}
		}
	};
}

#endif