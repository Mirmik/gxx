#ifndef GXX_MESSENGER_SENDER_H
#define GXX_MESSENGER_SENDER_H

#include <gxx/buffer.h>

namespace gxx {
	namespace msg {
		class sender {
		public:
			/*virtual void start() = 0;
			//virtual void add_part(gxx::buffer buf) = 0;
			virtual void finish() = 0;

			virtual void send(gxx::buffer buf) {
				start();
				part(buf);
				finish();
			}*/

		//	virtual void send(const gxx::vecbuf& buffs) = 0;
		};

		class receiver {
		public:
		//	virtual bool recv();
		};
	}
}

#endif