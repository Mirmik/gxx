#ifndef GXX_MATH_UTIL_H
#define GXX_MATH_UTIL_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <math.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

float veryquick_rsqrt( float number );
float quick_rsqrt( float number );

__END_DECLS

#ifdef __cplusplus
namespace gxx { namespace math {

	using ::veryquick_rsqrt;
	using ::quick_rsqrt;

	template <typename T, T prec>
	static inline bool is_same_template(T a, T b) {
		return fabs(a-b) < prec;
	}

	template <typename T, typename P>
	static inline bool is_same(T a, T b, P prec) {
		return fabs(a-b) < prec;
	}

	template <typename T, typename P>
	static inline bool early_zero(T a, P prec) {
		return fabs(a) < prec;
	}


	static inline double rad2angle(double r) {
		return r / 2 / M_PI * 360;
	}

	template<typename T> T maximum(T a, T b) { return a > b ? a : b; }
	template<typename T> T minimum(T a, T b) { return a < b ? a : b; }

	template<typename T>
	T limitation(const T& a, const T& min, const T& max) {
		return min > a ? min : max < a ? max : a;
	}

	inline double degree(double arg) {
		return arg * M_PI / 180;
	}
}}
#endif

/*
 * min()/max()/clamp() macros that also do
 * strict type-checking.. See the
 * "unnecessary" pointer comparison.
 */
/*#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })*/

/**
 * clamp - return a value clamped to a given range with strict typechecking
 * @val: current value
 * @min: minimum allowable value
 * @max: maximum allowable value
 *
 * This macro does strict typechecking of min/max to make sure they are of the
 * same type as val.  See the unnecessary pointer comparisons.
 */
/*#define clamp(val, min, max) ({			\
	typeof(val) __val = (val);		\
	typeof(min) __min = (min);		\
	typeof(max) __max = (max);		\
	(void) (&__val == &__min);		\
	(void) (&__val == &__max);		\
	__val = __val < __min ? __min: __val;	\
	__val > __max ? __max: __val; })*/

/*
 * ..and if you can't take the strict
 * types, you can specify one yourself.
 *
 * Or not use min/max/clamp at all, of course.
 */
/*#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1: __min2; })

#define max_t(type, x, y) ({			\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1: __max2; })*/

/**
 * clamp_t - return a value clamped to a given range using a given type
 * @type: the type of variable to use
 * @val: current value
 * @min: minimum allowable value
 * @max: maximum allowable value
 *
 * This macro does no typechecking and uses temporary variables of type
 * 'type' to make all the comparisons.
 */
/*#define clamp_t(type, val, min, max) ({		\
	type __val = (val);			\
	type __min = (min);			\
	type __max = (max);			\
	__val = __val < __min ? __min: __val;	\
	__val > __max ? __max: __val; })*/

#endif