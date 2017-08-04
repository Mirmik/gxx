#ifndef GXX_SPAM_SERVER_H
#define GXX_SPAM_SERVER_H

#include <gxx/inet/server.h>
#include <algorithm>
#include <list>

#include <string.h>
#include <gxx/format.h>

#include <gxx/debug.h>

namespace gxx {
	class spam_server : public server {

		std::list<gxx::socket> clients;

	public:
		spam_server(int port) : server(gxx::SocketType::Tcp, port) {};

		int start() {
			if (server::listen() < 0) { 
				gxx::debug("spam_server start error");
				return -1;
			}

			blocking(false);
			return 0;
		}

		int __send(const char* str) {
			return __send(str, strlen(str));
		};

		int __send(const char* str, size_t n) {
			//gxx::socket new_client;
			
			while(true) {
				gxx::socket new_client;
				int sts = try_accept(new_client);
				if (sts != 0) break;
				clients.push_back(std::move(new_client));
			}

			int ret = 0;
			bool needRemove = false;
			for(auto& c : clients) {

				//dprln("send");
				ret = c.write(str, n);
				dprln(ret);
				if (ret < 0) {
					needRemove = true;
				}
			}
			//int wrong = -1;
			if (needRemove)	{ 
				//dprln("needRemove");
				std::list<gxx::socket>::iterator it;
				auto next = clients.begin();
				auto end = clients.end();
				it = next;
				for(; it != end; it = next) {
					//dprln("HERE");
					next++;
					//dprln(it->is_connected());
					if (it->is_connected() == false) clients.erase(it);
				}
				//while(true);
			}


			return ret;
		}

		int writeData(const char* str, size_t sz) override {
			//dprln("writeData: {}", str);
			return __send(str, sz);
		}	
	
		int readData(char* str, size_t sz) override {}
	};
}

#endif