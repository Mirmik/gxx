#ifndef GXX_SERIALIZE_SCPI_H
#define GXX_SERIALIZE_SCPI_H

#include <vector>
#include <string>
#include <cctype>

#include <gxx/creader.h>

namespace gxx {
	using buffer_literal::operator"" _b;

	class scpi_string_parser {		

	public:
		struct header {
			std::string str;
			int num;

			header(const std::string& str, int num) : str(str), num(num) {}
		};

		std::vector<header> 		headers;
		std::vector<std::string> 	arguments;
		bool is_question = false;
		bool is_error = false;

	public:
		scpi_string_parser(std::string& str) {
			gxx::creader reader(str.c_str());

			while(reader.next_is(isalpha)) {
				std::string tempstr = reader.string_while(isalpha);
				int tempnum = reader.next_is(isdigit) ? reader.integer() : -1;
				headers.emplace_back(tempstr, tempnum);
				if (!reader.next_is(':')) break;
				else reader.skip(); 
			}

			reader.skip_while(' ');
			while(!reader.next_is("\0?"_b)) {
				if (reader.next_is(isalnum) == false) { is_error = true; return; }
				arguments.emplace_back(reader.string_while(isalnum));		
				reader.skip_while(" ,");			
			}

			if (reader.next_is('?')) is_question = true;
		}
	};
}

#endif