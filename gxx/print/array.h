#ifndef GXX_ARRAY_PRINT_H
#define GXX_ARRAY_PRINT_H

namespace gxx {
	template<typename T>
	class array_printable {
	public:
		size_t printTo(gxx::io::ostream& o) const {
			auto& self = *reinterpret_cast<const T*>(this);
			o.putchar('[');
			for (int i = 0; i < self.size(); ++i) {
				gxx::print(self[i]);
				if (i != self.size() - 1) o.putchar(' ');
			}
			o.putchar(']');
		}
	};
}
#endif