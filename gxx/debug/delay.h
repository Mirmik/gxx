#ifndef GXX_DEBUG_DELAY_H
#define GXX_DEBUG_DELAY_H

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

//void debug_delay(uint32_t ms);

static inline void debug_simple_delay(uint64_t ticks) {
	volatile uint64_t count = ticks;
	while(count--);
}

__END_DECLS

#endif