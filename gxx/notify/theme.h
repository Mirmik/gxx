#ifndef GXX_NOTIFY_THEME_H
#define GXX_NOTIFY_THEME_H

#include <gxx/dlist.h>
#include <gxx/notify/brocker.h>

namespace gxx {
	namespace notify {
		class subscriber;

		class theme {
			std::string identify;
			theme(const std::string& idn) : identify(idn) {}

			std::vector<gxx::notify::subscriber*> subs;  

			template< typename T >
			void notify(T& obj) {
				for (auto& s : subs) {
					s.subscriber->notify(identify, obj);
				}
			}

			void disconnect(subscriber* scb);
			void connect(subscriber* scb);
		};
	}
}

#endif