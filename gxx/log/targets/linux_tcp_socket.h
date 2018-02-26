#ifndef GXX_TARGET_LINUX_TCP_SOCKET_H
#define GXX_TARGET_LINUX_TCP_SOCKET_H

#include <gxx/logger/target.h>
#include <gxx/inet/spam_server.h>

namespace gxx { 
	namespace log {
		class spam_server_target : public target {
			spam_server server;
		public:
			spam_server_target(int port) : server(port) {}
	
			int start() {
				return server.start();
			}
	
			void log(const char* str) override {
				server.print(str);
			}
		};
	}
}

#endif