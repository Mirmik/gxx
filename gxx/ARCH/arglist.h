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

		argument(const int8_t& num, const char* name = nullptr) 		: i8 ( num ) , type (  SInt8 ), name(name) {}
		argument(const int16_t& num, const char* name = nullptr) 		: i16 ( num ) , type (  SInt16 ), name(name) {}
		argument(const int32_t& num, const char* name = nullptr) 		: i32 ( num ) , type (  SInt32 ), name(name) {}
		argument(const int64_t& num, const char* name = nullptr) 		: i64 ( num ) , type (  SInt64 ), name(name) {}
	
		argument(const uint8_t& num, const char* name = nullptr) 		: u8 ( num ) , type (  UInt8 ), name(name) {}
		argument(const uint16_t& num, const char* name = nullptr) 		: u16 ( num ) , type ( UInt16 ), name(name) {}
		argument(const uint32_t& num, const char* name = nullptr) 		: u32 ( num ) , type ( UInt32 ), name(name) {}
		argument(const uint64_t& num, const char* name = nullptr) 		: u64 ( num ) , type ( UInt64 ), name(name) {}
	
		argument(const char* const& str, const char* name = nullptr)	: str ( str  ) , type ( CharPtr ), name(name) {}

		argument(void* ptr, void* func, const char* name = nullptr)	: type(CustomType), custom(ptr, func), name(name) {}

		//custom is max sized type
		argument(const argument& other) = default;
		argument(argument&& other) = default;
	
		const char* type_to_string();
	};

	/*class argument_with_name : public argument {
	public:
		template<typename Arg> 
		argument_with_name(Arg&& arg) : argument(std::forward<Arg>(arg)) {};

		template<typename Arg, typename Arg2> 
		argument_with_name(Arg&& arg, Arg2&& arg2) 
			: argument(std::forward<Arg>(arg), std::forward<Arg2>(arg2)) {};
	};*/

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
			arglist_former(list, std::forward<UArgs>(args) ...);
			listsz = sizeof...(args);
		}

		const argument& operator[](int i) const;

		argument* begin();
		argument* end();

		int find_name(const char* name, size_t len) const;
	};

	template<typename Customer, typename T>
	gxx::enable_if_t<gxx::is_constructible<argument, T&>::value, argument> 
	make_argument(argpair<T>& arg) { 
		return argument(arg.body, arg.name); 
	}
	 
	template<typename Customer, typename T> 
	gxx::enable_if_t<!gxx::is_constructible<argument, T&>::value, argument> 
	make_argument(argpair<T>& arg) { 
		return argument(&arg.body, (void*) Customer::template function_pointer<T>(), arg.name); 
	}

	template<typename Customer, typename T>
	gxx::enable_if_t<gxx::is_constructible<argument, T&>::value, argument> 
	make_argument(T&& arg) { 
		return argument(std::forward<T>(arg)); 
	}
	 
	template<typename Customer, typename T> 
	gxx::enable_if_t<!gxx::is_constructible<argument, T&>::value, argument> 
	make_argument(T&& arg) { 
		return argument(&arg, (void*) Customer::template function_pointer<T>()); 
	}


}

#endif