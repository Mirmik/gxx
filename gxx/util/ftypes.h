#ifndef GXX_UTIL_FTYPES_H
#define GXX_UTIL_FTYPES_H

#include <asm/types.h>

#ifdef SFLOAT_DEFINED
typedef __sfloat sfloat;
#else
typedef float sfloat;
#endif
static_assert(sizeof(sfloat) == 4, "wrong sfloat type size");

#ifndef WITHOUT_DFLOAT
#	ifdef DFLOAT_DEFINED
	typedef __dfloat dfloat;
#	else
	typedef double dfloat;
#	endif
	static_assert(sizeof(dfloat) == 8, "wrong dfloat type size");
#endif



#endif