#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

#include <gxx/serialize/json_parser.h>
#include <gxx/iteratible.h>

namespace gxx {
	namespace detail {
		template<char Delimiter> class split_helper : public std::string {};

		template<char Delimiter> 
		std::istream& operator>>(std::istream& is, split_helper<Delimiter>& output) {
			std::getline(is, output, Delimiter);
			return is;
		}
	}

	class json_settings {
	public:
		json m_settings;

		std::string pathstr;

		json_settings(const char* path) : pathstr(path) {};

		
		void load() {
			std::fstream file(pathstr);

			std::stringstream file_contents;
			file_contents << file.rdbuf();
			m_settings = json_parser::parse(file_contents).unwrap();

			file.close();
		}

		json& settings() {
			return m_settings;
		}

		void save() {
			std::fstream file(pathstr);

			m_settings.prettyPrintTo(file);
			
			file.close();
		}

		int64_t get_number(const char* str, int64_t def) {
			json* cur = &m_settings;
			for (auto& s : gxx::split_tokenizer(str, '/')) {
				if (cur->contains(s)) cur = (json*)&((*cur)[s]);
				else return def;
			}            
			if (cur->get_type() != gxx::datatree::type::integer) return def;
			return cur->as_integer();
		}

		int64_t get_number(const std::string& str, int64_t def) {
			return get_number(str.c_str(), def);
		}
	};
}

#endif