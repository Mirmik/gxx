#ifndef GXX_PLACED_NEW_H
#define GXX_PLACED_NEW_H

#include <stdlib.h>

//template<typename T>
void* operator new(size_t, void* __p) noexcept;

#endif