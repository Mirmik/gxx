#define CONCAT(a,b) a##b
#define CONCAT2(a,b) CONCAT(a,b)

#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGS(...) ELEVENTH_ARGUMENT(_, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define Dpr0(...)        CONCAT(dpr_, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)
#define Dpr1(...)        CONCAT2(dpr_, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)

Dpr0(x, y)
Dpr1(x, y)