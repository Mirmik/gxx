#ifndef GXX_EVENT_H
#define GXX_EVENT_H

#include <gxx/dlist.h>
#include <gxx/delegate.h>

namespace gxx {
	namespace event {
		class waiter_processor;

		class waiter {
		public:
			dlist_head lnk;
			waiter_processor* processor;
			gxx::delegate<void> dlg;
		};

		class waiter_processor {
			dlist<waiter, &waiter::lnk> list;

			void execute() {
				while(!list.empty()) {
					auto& ref = *list.begin();
					list.pop(ref);
					ref.dlg();
				}
			}
		};

		class waiter_head {
		public:
			dlist<waiter, &waiter::lnk> list;

			void emit_node(waiter*) {

			}

			void emit() {

			}
		};

		class flag : public waiter_head {
		public:
		};
	}
}

#endif