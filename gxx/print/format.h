#ifndef GXX_FMT_FORMAT_H
#define GXX_FMT_FORMAT_H

#include <gxx/arglist.h>

namespace gxx
{
	namespace io
	{
		class ostream;
	}

	namespace fmt
	{
		//Форматирующий визитёр для arglist.
		struct format_visitor
		{
			using ftype = int(*)(void*, gxx::io::ostream&, gxx::buffer opts);

			template<typename Object>
			static void* get_visit()
			{
				return reinterpret_cast<void*>(&fprint_functions<Object>::format_print);
			}

			template<typename ... Args>
			static inline int visit(gxx::visitable_argument varg, Args&& ... args)
			{
				ftype fptr = (ftype) varg.visit;
				return fptr(varg.ptr, std::forward<Args>(args) ...);
			}
		};
	}
}

#endif