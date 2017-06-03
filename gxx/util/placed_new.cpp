#include <gxx/util/placed_new.h>

void* operator new(size_t, void* __p) noexcept {
	return __p;
}