#ifndef EMTEST_H_
#define EMTEST_H_

struct test_suite_desc {
	const char* desc;
};

#include <gxx/util/macro.h>
#include <gxx/datastruct/array_spread.h>

ARRAY_SPREAD_DECLARE(struct test_suite_desc *, all_tests);

#endif /* EMTEST_H_ */