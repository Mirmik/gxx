#ifndef GXX_PRECISSION_H
#define GXX_PRECISSION_H

namespace gxx {
	namespace math {
		template <typename T> struct precision_analog;
		template <> struct precision_analog<double> { using type = double; };
		template <> struct precision_analog<float> { using type = float; };

		template <> struct precision_analog<int8_t> { using type = float; };
		template <> struct precision_analog<int16_t> { using type = float; };
		template <> struct precision_analog<int32_t> { using type = float; };
		template <> struct precision_analog<int64_t> { using type = float; };

		template <> struct precision_analog<uint8_t> { using type = float; };
		template <> struct precision_analog<uint16_t> { using type = float; };
		template <> struct precision_analog<uint32_t> { using type = float; };
		template <> struct precision_analog<uint64_t> { using type = float; };
	}
}

#endif