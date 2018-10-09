#ifndef GXX_UTIL_GMSG_H
#define GXX_UTIL_GMSG_H

//Определение стаффирующих байтов для протокола gstuff.

namespace gxx {
	namespace gmsg {
		constexpr unsigned char strt = 0xAC;
		constexpr unsigned char stub = 0xAD;
		constexpr unsigned char stub_strt = 0xAE;
		constexpr unsigned char stub_stub = 0xAF;
	} 
}

#endif