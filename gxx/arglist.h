#ifndef GXX_ARGSLIST_H
#define GXX_ARGSLIST_H

#include <string.h>
#include <gxx/buffer.h>
#include <gxx/utility.h>
#include <gxx/debug/dprint.h>
#include <gxx/debug/type_analize.h>

namespace gxx {	
	template <typename T> class argpair; 

	struct argname {
		const char*& name;
		argname(const char*& name) : name(name) {}; 
		template<typename T> 
		constexpr argpair<T> operator= (const T& body) {  return argpair<T>(name, body); }  
	};
	
	template<typename T>
	struct argpair {
		const T& body;
		const char* name;
		constexpr argpair(const char* name, const T& body) : body(body), name(name) {}
	};

	namespace literals {
		static argname operator"" _a (const char* name, size_t sz) { return argname(name); } 
	}

	struct argument {
		void* ptr;
		void* func; 

	public:
		argument(){};

		template <typename T>
		argument(T&& arg, void* func) : ptr((void*)&arg), func(func) {}
	};

	template<typename HT, typename ... Tail>
	static inline void arglist_former(argument* argptr, const HT& head, const Tail& ... tail) {
		new (argptr) argument( head );
		arglist_former(++argptr, tail ...);
	}

	static inline void arglist_former(argument* argptr) {}
	
	class arglist {
	public:
		argument list[10];
		size_t listsz;
	
		template<typename ... UArgs>
		explicit arglist(UArgs&& ... args) {
			arglist_former(list, gxx::forward<UArgs>(args) ...);
			listsz = sizeof...(args);
		}
		const argument& operator[](int i) const;

		argument* begin();
		argument* end();
	};

	template<typename Customer, typename T>
	argument make_argument(T&& arg) {
		using DecayType = typename gxx::decay<T>::type;  
		return argument(static_cast<DecayType>(arg), (void*) Customer::template function_pointer<DecayType>()); 
	}
}

#endif