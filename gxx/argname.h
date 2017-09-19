#ifndef GXX_ARGPAIR_H
#define GXX_ARGPAIR_H

#include <gxx/buffer.h>

namespace gxx {
	template <typename T> class argpair; 
	struct argname {
		gxx::buffer name;
		argname(const gxx::buffer& name) : name(name) {}; 
		
		template<typename T> 
		constexpr argpair<std::remove_reference_t<T>> operator= (T&& body) { 
			return argpair<std::remove_reference_t<T>>(name, &body);
		}
	};
	
	template<typename T>
	struct argpair {
		using type = T;

		const void* body;
		gxx::buffer name;

		constexpr argpair(const gxx::buffer& name, const void* body) : body(body), name(name) {}
	};
	
	namespace argument_literal {
		static argname operator"" _a (const char* name, size_t sz) { 
			return argname(gxx::buffer(name, sz)); 
		} 
	}
}

#endif
