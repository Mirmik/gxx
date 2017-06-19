#ifndef GXX_MESSAGE_BROCKER_H
#define GXX_MESSAGE_BROCKER_H

namespace gxx {
	namespace msg {
		class brocker {
			gxx::server srv;

			std::map<uint16_t, std::shared_ptr<gxx::msg::gate>> conts;

			brocker(int port) : srv(port) {}

			void start() {
				server.start();
			}

			void work_loop() {

			}
		};
	}
}

#endif