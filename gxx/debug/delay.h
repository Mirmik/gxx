#ifndef GXX_DEBUG_DELAY_H
#define GXX_DEBUG_DELAY_H

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

extern double __debug_delay_multiplier;

extern void debug_simple_delay(uint64_t ticks);
extern void debug_delay(uint32_t ms);

__END_DECLS

#endif