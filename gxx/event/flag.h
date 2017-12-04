#ifndef GXX_EVENT_FLAG_H
#define GXX_EVENT_FLAG_H

#include <gxx/event/delegate.h>

namespace gxx {
	namespace event {
		class flag {
		public:
			virtual void set() = 0;
			virtual void clr() = 0;
			virtual bool setted() = 0;
		};

		class action_flag : public flag {
			bool f_en = false;
			bool d_en;
			gxx::action act;

			void check() {
				if (f_en && d_en) {
					d_en = false;
					act();
				}
			}

		public:	
			void set() override {
				f_en = true;
				check();
			}

			void clr() override {
				f_en = false;
			}

			bool setted() override {
				return f_en;
			}

			bool wait() {
				d_en = true;
				check();
			}

			void set_handler(gxx::action act, bool en = true) {
				d_en = false;
				this->act = act;
				if (en) wait();
			}
		};
	}
}

#endif