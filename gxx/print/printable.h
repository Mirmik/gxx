#ifndef GXX_ARRAY_PRINT_H
#define GXX_ARRAY_PRINT_H

#include <gxx/print.h>

//Классы, определяющие печатающие методы для типовых структур данных.
namespace gxx
{
	template<typename T>
	class array_printable
	{
	public:
		size_t printTo(gxx::io::ostream& o) const
		{
			int ret = 0;

			const auto& self = *reinterpret_cast<const T*>(this);
			ret += o.putchar('[');
			for (uint i = 0; i < self.size(); ++i)
			{
				ret += gxx::print(self[i]);
				if (i != self.size() - 1)
					ret += o.putchar(' ');
			}
			ret += o.putchar(']');

			return ret;
		}
	};

	template<typename T>
	class matrix_printable
	{
	public:
		size_t printTo(gxx::io::ostream& o) const
		{
			int ret = 0;

			const auto& self = *reinterpret_cast<const T*>(this);
			for (uint i = 0; i < self.size1(); ++i)
			{
				for (uint j = 0; j < self.size2(); ++j)
				{
					ret += gxx::print(self(i, j));
					ret += o.putchar(' ');
				}
				ret += o.println();
			}

			return ret;
		}
	};
}
#endif