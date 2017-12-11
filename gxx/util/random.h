#ifndef GXX_UTIL_RANDOM_H
#define GXX_UTIL_RANDOM_H

inline float float_random(float a, float b) {
	return a + (rand() * (b - a) / RAND_MAX);
}

#endif