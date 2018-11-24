#ifndef GENOS_LOCATION_H
#define GENOS_LOCATION_H

//Определение позиции в коде. Для трассировки.
#include <gxx/debug/dprint.h>

struct location {
	int line;
	const char* file;
	const char* func;
};

#define CURRENT_LOCATION(name)				\
	struct location name = { __LINE__, __FILE__, __func__ };

#define CURRENT_LOCATION_INITARGS __LINE__,__FILE__,__func__

static inline void debug_print_location(struct location location) {
	debug_print("file: "); dpr(location.file); dln();
	debug_print("func: "); dpr(location.func); dln();
	debug_print("line: "); dpr(location.line); dln();
}

#endif /* UTIL_LOCATION_H_ */
