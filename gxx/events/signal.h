#ifndef GXX_EVENTS_SIGNAL_H
#define GXX_EVENTS_SIGNAL_H

#include <gxx/dlist.h>
#include <gxx/delegate.h>

namespace gxx {
	template <typename ... Args>
	class basic_slot {
	public:
		virtual void invoke(Args ... args) = 0;
	
		//manage
		dlist_head lnk;
	};

	template <typename ... Args>
	class slot : public basic_slot<Args ...> {
		using Parent = basic_slot<Args ...>;

		delegate<void, Args ...> dlg;

	public:
		slot(gxx::delegate<Args ...> dlg) : dlg(dlg) {}
		slot(void(*func)(Args ...)) : dlg(func) {}

		void invoke(Args ... args) {
			dlg(args ...);
		}
	};

	template <typename ... Args>
	class signal {
		using Slot = basic_slot<Args ...>;

	public:
		dlist<Slot, &Slot::lnk> slots;

		void connect(Slot& slt) {
			slots.move_back(slt);
		}

		virtual void emit(Args ... args) {
			gxx::for_each_safe(slots.begin(), slots.end(), [&](Slot& slt) {
				slt.invoke(args ...);
			});
		} 

		virtual void emit_one(Args ... args) {
			slots.begin()->invoke(args ...);
		} 
	};
}

#endif