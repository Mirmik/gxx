#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <string>
#include <sstream>
#include <fstream>

#include <gxx/trent/json.h>
#include <gxx/trent/settings.h>

namespace gxx {
	class json_settings : public trent_settings_basic {
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

		void sync() {
			load();
			if (!m_settings.is_dict()) {
				m_settings = gxx::trent(gxx::trent::type::dict);
				save();
			}
		}

		void save() override {
			std::fstream file(pathstr, std::ios_base::trunc | std::ios::out);
			if (!file.good()) {
				PANIC_TRACED();
			}
			json::pretty_print_to(m_settings, file);	
			file.close();
		}

		bool ok() override {
			return m_settings.is_dict();
		}

		virtual gxx::trent& create(const std::string& str, const std::string&) {
			PANIC_TRACED();
		}

		virtual gxx::trent& create(const std::string& str, int) {
			PANIC_TRACED();
		}

		trent& root() {
			return m_settings;
		}

		trent& node() {
			return m_settings;
		}

                const trent& node() const {
                        return m_settings;
                }

		trent& operator[](const std::string& arg) {
			return m_settings[arg];
		}

		/*trent& get(const std::string& arg) override {
			return m_settings[arg];
		}*/

		trent& at(const std::string& arg) override {
			if (m_settings.is_dict() == false) PANIC_TRACED("settings isn't dict");
			if (!m_settings.have(arg)) PANIC_TRACED("settings doesn't have option");
			return m_settings[arg];
		}

                const trent& operator[](const std::string& arg) const {
			return m_settings[arg];
		}

		operator trent&() {
			return m_settings;
		}
	};
}

#endif
