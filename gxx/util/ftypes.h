#ifndef GXX_UTIL_FTYPES_H
#define GXX_UTIL_FTYPES_H

#include <asm/types.h>

#ifndef SFLOAT_DEFINED
typedef float sfloat;
#endif

#ifndef DFLOAT_DEFINED
typedef double dfloat;
#endif

static_assert(sizeof(sfloat) == 4, "wrong sfloat type size");
static_assert(sizeof(dfloat) == 8, "wrong dfloat type size");
	
#endif