#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <string>
#include <sstream>
#include <fstream>

#include <gxx/serialize/json.h>


namespace gxx {

	class json_settings {
		trent m_settings;
		std::string pathstr;

	public:
		ACCESSOR(path, pathstr);

		json_settings() = default;
        json_settings(const std::string& str) : pathstr(str) {};

		void load() {
			std::fstream file(pathstr);
			if (!file.good()) return;
			std::stringstream file_contents;
			file_contents << file.rdbuf();
			m_settings = json::parse(file_contents).unwrap();
			file.close();
		}

		void save() {
			std::fstream file(pathstr, std::ios_base::trunc | std::ios::out);
			json::pretty_print_to(m_settings, file);	
			file.close();
		}

		bool ok() {
			return !m_settings.is_nil();
		}

		trent& root() {
			return m_settings;
		}

		trent& operator[](const auto& arg) {
			return m_settings[arg];
		}

		operator trent&() {
			return m_settings;
		}
	};
	
}

#endif
