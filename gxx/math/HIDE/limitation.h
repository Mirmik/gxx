#ifndef GXX_MATH_LIMITATION_H
#define GXX_MATH_LIMITATION_H

namespace gxx {
    namespace math {

        template<typename T>
        T limitation(const T& a, const T& min, const T& max) {
            return min > a ? min : max < a ? max : a;
        }

    }
}

#endif
