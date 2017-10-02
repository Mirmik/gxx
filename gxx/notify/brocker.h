#ifndef GXX_NOTIFY_BROCKER_H
#define GXX_NOTIFY_BROCKER_H

namespace gxx {
	namespace notify {
		class notify_channel {

		};

		class console_control_channel : public notify_channel, public subscriber {
			gxx::iostream* io;

			void thread_function() {
				while(1) {
					std::string str = io->read_string();
					auto splt = gxx::split(str);
				
					if () {
						theme = brocker->themes[splt[0]];
						theme->connect(this);
					}
				}
			}

			template<typename T>
			void notify(const std::string& idn, const T& obj) {
				io->print(idn);
				io->print("::");
				io->print(obj);
			}
		};

		class brocker {
			theme* create_theme_for_signal(const std::string&);
		};
	}
}

#endif