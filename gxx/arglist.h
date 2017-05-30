#ifndef GXX_ARGSLIST_H
#define GXX_ARGSLIST_H

#include <string.h>
#include <gxx/buffer.h>
#include <gxx/utility.h>
#include <gxx/debug/dprint.h>

namespace gxx {	
	template <typename T> class argpair; 

	struct argname {
		const char*& name;
		argname(const char*& name) : name(name) {}; 
		template<typename T> 
		constexpr argpair<T> operator= (const T& body) { return argpair<T>(name, body); }  
	};
	
	template<typename T>
	struct argpair {
		const T& body;
		const char* name;
		constexpr argpair(const char* name, const T& body) : body(body), name(name) {}
	};

	namespace literals {
		argname operator"" _a (const char* name, size_t sz);
	}

	struct argument {
		struct custom_value {
			void* ptr;
			void* func; 
			custom_value(void* ptr, void* func) : ptr(ptr), func(func) {};
		};

		enum Type {
			SInt8,
			SInt16,
			SInt32,
			SInt64,
			UInt8,
			UInt16,
			UInt32,
			UInt64,
			CharPtr,
			CustomType,
		};
	
		union {
			const int8_t& i8;
			const int16_t& i16;
			const int32_t& i32;
			const int64_t& i64;
			const uint8_t& u8;
			const uint16_t& u16;
			const uint32_t& u32;
			const uint64_t& u64;
			const char* str;
			custom_value custom;
		};

	
		Type type;
		const char* name;

		argument(){}

		argument(const int8_t& num) 		: i8 ( num ) , type (  SInt8 ) {}
		argument(const int16_t& num) 		: i16 ( num ) , type (  SInt16 ) {}
		argument(const int32_t& num) 		: i32 ( num ) , type (  SInt32 ) {}
		argument(const int64_t& num) 		: i64 ( num ) , type (  SInt64 ) {}
	
		argument(const uint8_t& num) 		: u8 ( num ) , type (  UInt8 ) {}
		argument(const uint16_t& num) 		: u16 ( num ) , type ( UInt16 ) {}
		argument(const uint32_t& num) 		: u32 ( num ) , type ( UInt32 ) {}
		argument(const uint64_t& num) 		: u64 ( num ) , type ( UInt64 ) {}
	
		argument(const char* const& str)	: str ( str  ) , type ( CharPtr ) {}

		argument(void* ptr, void* func)	: type(CustomType), custom(ptr, func) {}

		//custom is max sized type
		argument(const argument& other) : custom(other.custom), type(other.type) {}
	
		const char* type_to_string();
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

		/*int find_name(const char* name, size_t len) const {
			for(int i = 0; i < 10; ++i) {
				if (list[i].name && !strncmp(name, list[i].name, len)) return i; 
			}
			return -1;
		}*/
	};

	template<typename Customer, typename T>
	gxx::enable_if_t<gxx::is_constructible<argument, T&>::value, argument> 
	make_argument(T&& arg) { 
		return argument(gxx::forward<T>(arg)); 
	}
	 
	template<typename Customer, typename T> 
	gxx::enable_if_t<!gxx::is_constructible<argument, T&>::value, argument> 
	make_argument(T&& arg) { 
		return argument(&arg, (void*) Customer::template function_pointer<T>()); 
	}
}

#endif