#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

//#include <gxx/strvec.h>
#include <gxx/serialize/json_parser.h>

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
		//datatree m_default;
		json m_settings;

		std::string pathstr;

		json_settings(const char* path) : pathstr(path) {};

		
		void load() {
			std::fstream file(pathstr);

			std::stringstream file_contents;
			file_contents << file.rdbuf();
			//std::cout << file_contents.str() << std::endl;
			m_settings = json_parser::parse(file_contents).unwrap();

			//m_settings.merge(m_default, gxx::datatree::MergeType::WeakMerge);
		}

		void save() {
			std::fstream file(pathstr);
			m_settings.prettyPrintTo(file);
		}

		//json& operator[](std::string str) {
		//	return root[str];
		//}

		int64_t get_number(const char* str, int64_t def) {
			std::istringstream iss { std::string(str) };
			std::vector<std::string> vec(
				(std::istream_iterator<detail::split_helper<'/'>>(iss)),
                std::istream_iterator<detail::split_helper<'/'>>()
            );

			for (const auto& s : vec) {
				dprln(s);
			}            
		}
	};

}

#endif