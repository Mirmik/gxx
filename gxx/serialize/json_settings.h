#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>

#include <gxx/serialize/json_parser.h>
//#include <gxx/iteratible.h>

#include <unistd.h>


namespace gxx {

	class json_settings {
	public:
		json m_settings;
		std::string pathstr;

		ACCESSOR(path, pathstr);

		json_settings() = default;
		json_settings(const char* path) : pathstr(path) {};
                json_settings(const std::string& str) : pathstr(str) {};

		void load() {
			std::fstream file(pathstr);
			std::stringstream file_contents;
			file_contents << file.rdbuf();
			m_settings = json_parser::parse(file_contents).unwrap();
			//m_settings.prettyPrintTo(std::cout);
			file.close();
		}

		void save() {
			dprln(pathstr);
			std::fstream file(pathstr, std::ios_base::trunc | std::ios::out);
			dprln(file.good());
			m_settings.prettyPrintTo(file);	
			file.close();
		}

		json& settings() {
			return m_settings;
		}
	};
	
}

#endif
