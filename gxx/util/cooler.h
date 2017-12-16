#ifndef GXX_COOLER_H
#define GXX_COOLER_H

#include <utility>
#include <gxx/print.h>
#include <typeinfo>

namespace gxx {
	template <typename T> class cooler;

	template <typename T> class cooler<T&> {
	public:
		T& ref;
		cooler(const T& ref) : ref(ref) {
			dprln("T&");
		}
		cooler(const cooler& c) : ref(c.ref) {}
		auto operator->() { return &ref; }
	};

	template <typename T> class cooler<T&&> {
	public:
		T ref;
		cooler(T&& ref) : ref(std::move(ref)) {
		}
		cooler(const cooler& c) : ref(c.ref) {
		}
		cooler(cooler&& c) : ref(std::move(c.ref)) {
		}
		//cooler(const cooler& c) : ref(c.ref) {}
		auto operator->() { return &ref; }
	};
}

#endif