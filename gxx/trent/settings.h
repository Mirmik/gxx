#ifndef GXX_TRENT_SETTINGS_H
#define GXX_TRENT_SETTINGS_H

namespace gxx {

	class trent_settings_basic {
	public:
		virtual gxx::trent& at(const std::string& str) = 0;
		virtual gxx::trent& operator[](const std::string& str) = 0;
		//virtual gxx::trent& create(const std::string& str, const std::string&) = 0;
		//virtual gxx::trent& create(const std::string& str, int) = 0;

		virtual bool ok() = 0;
		virtual void save() = 0;
		virtual void sync() = 0;
		virtual trent& node() = 0;
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

		gxx::trent& operator[](const std::string& str) override {
			return node()[str];
		}
		
		/*
		gxx::trent& create(const std::string& str, const std::string&) override {
			PANIC_TRACED();
		}

		gxx::trent& create(const std::string& str, int) override {
			PANIC_TRACED();
		}*/

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
				rt = &(*base)[name];
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

	class settings_binder {
	public:
		trent_settings_basic& settings;
		std::string name;
		trent* tr = nullptr;

		settings_binder(trent_settings_basic& base, const std::string& name) : name(name), settings(base) {}

		void save() { settings.save(); }
	};

	class settings_binder_integer : public settings_binder {
	public:
		settings_binder_integer(trent_settings_basic& base, const std::string& name) : settings_binder(base, name) {}

		void sync_default(trent::integer_type def) {
			tr = &settings[name];
			if (tr->is_nil()) *tr = def; 
		}

		settings_binder_integer& operator++() {
			*tr = (*tr).as_integer() + 1;
			return *this;
		}

		settings_binder_integer& operator++(int) {
			*tr = (*tr).as_integer() + 1;
			return *this;
		}

		operator trent::integer_type() const { return tr->as_integer(); }
	};

	class settings_binder_numer : public settings_binder {
	public:
		settings_binder_numer(trent_settings_basic& base, const std::string& name) : settings_binder(base, name) {}

		void sync_default(trent::numer_type def) {
			tr = &settings[name];
			if (tr->is_nil()) *tr = def; 
		}

		settings_binder_numer& operator+=(const trent::numer_type& add) {
			*tr = (*tr).as_numer() + add;
			return *this;
		}

		operator trent::numer_type() const { return tr->as_numer(); }
	};
}

#endif