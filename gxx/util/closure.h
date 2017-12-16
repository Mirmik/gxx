#ifndef GXX_COOLER_H
#define GXX_COOLER_H

#include <utility>
#include <gxx/print.h>

namespace gxx {
	template <typename T> class closure;

	template <typename T> class closure<T&> {
	public:
		T& ref;
		closure(const T& ref) : ref(ref) {}
		closure(const closure& c) : ref(c.ref) {}
		auto operator->() { return &ref; }
	};

	template <typename T> class closure<T&&> {
	public:
		T ref;
		closure(T&& ref) : ref(std::move(ref)) {}
		closure(const closure& c) : ref(c.ref) {}
		auto operator->() { return &ref; }
	};
}

#endif