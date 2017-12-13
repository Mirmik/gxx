#ifndef GXX_UTIL_RANDOM_H
#define GXX_UTIL_RANDOM_H

inline float float_random(float a, float b) {
	return a + (rand() * (b - a) / RAND_MAX);
}

namespace gxx {
	template<typename T> 
	inline T random_minmax(const T& minval, const T& maxval);

	template<> 
	inline float random_minmax<float>(const float& a, const float& b) {
		return a + (rand() * (b - a) / RAND_MAX);
	}	
}

#endif