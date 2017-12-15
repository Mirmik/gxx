#ifndef GXX_COOLER_H
#define GXX_COOLER_H

#include <utility>
#include <gxx/print.h>

namespace gxx {
	template <typename T> class cooler;

	template <typename T> class cooler<T&> {
	public:
		T& ref;
		cooler(const T& ref) : ref(ref) {}
		cooler(const cooler& c) : ref(c.ref) {
			gxx::println("refcopy");
		}
		auto operator->() { return &ref; }
	};

	template <typename T> class cooler<T&&> {
	public:
		T ref;
		cooler(T&& ref) : ref(std::move(ref)) {}
		cooler(const cooler& c) : ref(c.ref) {
			gxx::println("copy");
		}
		auto operator->() { return &ref; }
	};
}

#endif