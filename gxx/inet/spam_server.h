#ifndef GXX_SPAM_SERVER_H
#define GXX_SPAM_SERVER_H

#include <gxx/algorithm.h>
#include <gxx/inet/server.h>
#include <gxx/vector.h>

#include <string.h>

namespace gxx {
	class spam_server : public server {

		gxx::vector<int> clients;

	public:
		spam_server(int port) : server(port) {};

		void start(int maxcon) {
			server::start(maxcon);
			blocking(false);
		}

		void send(const char* str) {
			send(str, strlen(str));
		};

		void send(const char* str, size_t n) {
			int new_client;
			while((new_client = accept()) >= 0) {
				//dprln("new");
				clients.push_back(new_client);
			}

			bool needRemove = false;
			for(auto&& c : clients) {
				//dprln("send");
				int ret = ::send(c, str, n, MSG_NOSIGNAL);
				if (ret < 0) {
					c = -1;
					needRemove = true;
				}
			}
			//int wrong = -1;
			if (needRemove)	{ 
				clients.erase(gxx::remove(clients.begin(), clients.end(), -1));
			}
		}
	};
}

#endif