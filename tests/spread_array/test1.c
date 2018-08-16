#include <stdio.h>
#include <stddef.h>

#include "gxx/datastruct/array_spread.h"
#include "test.h"

struct test_suite_desc t1 = {"t1"};

ARRAY_SPREAD_ADD(all_tests, &t1);