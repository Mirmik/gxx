#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <string>
#include <sstream>
#include <fstream>

#include <gxx/trent/json.h>


namespace gxx {

        class trent_settings_basic {
        public:
            virtual gxx::trent& at(const std::string& str) = 0;
            virtual gxx::trent& get(const std::string& str) = 0;
            virtual gxx::trent& create(const std::string& str, const std::string&) = 0;
            virtual gxx::trent& create(const std::string& str, int) = 0;

            virtual bool ok() = 0;
            virtual void save() = 0;
            virtual void sync() = 0;
            virtual trent& node() = 0;
        };

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

                trent& operator[](const auto& arg) {
                    return m_settings[arg];
		}

                trent& get(const std::string& arg) override {
                    return m_settings[arg];
                }

                trent& at(const std::string& arg) override {
                    if (m_settings.is_dict() == false) PANIC_TRACED("settings isn't dict");
                    if (!m_settings.have(arg)) PANIC_TRACED("settings doesn't have option");
                    return m_settings[arg];
                }

		const trent& operator[](const auto& arg) const {
			return m_settings[arg];
		}

		operator trent&() {
			return m_settings;
		}
	};

        class settings_slice : public trent_settings_basic {
            trent_settings_basic* base;
            std::string name;
            gxx::trent* rt = nullptr;

        public:
            settings_slice(trent_settings_basic& base, const std::string name) : base(&base), name(name) {}

            gxx::trent& at(const std::string& str) override {
                PANIC_TRACED();
            }

            gxx::trent& get(const std::string& str) override {
                PANIC_TRACED();
            }

            gxx::trent& create(const std::string& str, const std::string&) override {
                PANIC_TRACED();
            }

            gxx::trent& create(const std::string& str, int) override {
                PANIC_TRACED();
            }

            void save() override {
                base->save();
            }

            bool ok() override {
                return (rt && rt->is_dict());
            }

            trent& node() {
                return *rt;
            }

            void sync() override {
                if (base->ok()) {
                    rt = &base->get(name);
                    if (!rt->is_dict()) {
                        gxx::println("create new slice");
                        *rt = gxx::trent(gxx::trent::type::dict);
                        save();
                    }
                } else {
                    PANIC_TRACED();
                }
            }
        };

}

#endif
