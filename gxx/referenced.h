#ifndef GXX_REFERENCED_H
#define GXX_REFERENCED_H

namespace gxx {
	/*template <RefType, typename ImplType>
	class referenced : public RefType {
		uint16_t refs;
		ImplType* impl;

		template<typename ... Args>
		referenced(Args&& ... args) : refs(1) {
			impl = new ImplType(std::forward<Args ...>(args));
		}

		referenced(const RefType& oth) {
			impl = oth.impl;

		}
	}*/
}

#endif