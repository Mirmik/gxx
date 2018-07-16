#ifndef GXX_REFCONTROL_H
#define GXX_REFCONTROL_H

#include <stdint.h>

namespace gxx {
	template <class T, uint8_t T::* R, void(T::* Get)() = &T::ref_get, void(T::* Put)() = &T::ref_put>
	class refcontrol {
	private:
		T* obj;

		void plus() {
			if ((obj->*R) ++ == 0) {
				(obj->*Get)();
			}	
		}

		void minus() {			
			if (-- (obj->*R) == 0) {
				(obj->*Put)();
			}	
		}

	public:
		refcontrol(T* obj) : obj(obj) {
			plus();
		}

		~refcontrol() {
			minus();
		}

		refcontrol(const refcontrol&) = delete;
		refcontrol(refcontrol&& oth) : obj(oth.obj) { oth.obj = nullptr; }

		void detach() {
			if (obj) minus();
			obj = nullptr;
		}

		T* getobj() { return obj; }
	};
}

#endif