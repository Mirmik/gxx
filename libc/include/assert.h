#ifndef ASSERT_H_
#define ASSERT_H_

#include <gxx/debug/dprint.h>

static inline void __assert(const char* message, const char* file, int line) { debug_print_line("assert"); while(1); }
#define assert(EX) (void)((EX) || (__assert (#EX, __FILE__, __LINE__),0))

#ifndef __cplusplus
#	define static_assert(a,b) _Static_assert(a,b)
#endif

#endif /* ASSERT_H_ */
