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
		const T* body;
		const char* name;
		constexpr argpair(const char* name, const T& body) : body(&body), name(name) {}
	};

	template<typename T>
	struct argument {
		const T& ref;
	//public:
		explicit constexpr argument(const T& ref) : ref(ref) {}
	};

	template<typename T>
	struct argument<argpair<T>> {
		const argpair<T>& pair;
	//public:
		explicit constexpr argument(const argpair<T>& ref) : pair(ref) {}
	};

	template<typename T>
	struct argument<gxx::object_buffer<T>> {
		gxx::object_buffer<T> buf;
		
		template<typename InArg> inline constexpr argument(InArg in);

		template<size_t N>
		inline constexpr argument(T(&arr)[N]) : buf(arr) {}

		//template<>
		//inline constexpr argument(T* arr) : buf(arr) {}
	};

	template<typename InArg> struct make_argument {
		using InType = InArg;
		using Type = typename gxx::remove_reference<InArg>::type;
		static const argument<Type> doit(const InType& arg) { return argument<Type>(arg); }
	};
	
	template<typename T, size_t N> struct make_argument<T(&)[N]> {
		using InType = T(&)[N];
		using Type = typename gxx::remove_reference<gxx::object_buffer<T>>::type;
		static const argument<Type> doit(const InType& arg) { return argument<Type>(arg); }
	};
	
	/*template<> struct make_argument<> {
		static void do() {}
	};*/



	/*template<typename T, size_t N>
	struct argument<T(&)[N]> {
		gxx::object_buffer<T> buf;
	//public:
		constexpr argument(T(&arr)[N]) : buf(arr) {}
	};*/

	/*template<>
	struct argument<char*> {
		gxx::buffer buf;
		argument(char* ptr) : buf(ptr) {}
	};*/

	/*template<typename T, size_t N>
	struct argument<T(*)[N]> {
		gxx::buffer buf;
		argument(const char* ptr) : buf(ptr) {}
	};*/

	namespace literals {
		argname operator"" _a (const char* name, size_t sz) { return argname(name); } 
	}

	template<typename Generic>
	struct argument_header {
		using FuncType = decltype(&Generic::template genfunc<void>);

		void* ptr;
		FuncType funcptr;
		const char* name;
		
		argument_header(){}

		argument_header(void* ptr, void* funcptr, char const* name) :
			ptr(ptr), funcptr(funcptr), name(name) {}

		//DEBUG
		void debug_print() {
			std::cout << ptr << '\t' << funcptr << std::endl;
			if (name) std::cout << name << std::endl;
		}
	};


	template<typename Generic, typename ... Args> struct arglist_former;

	template<typename Generic> struct arglist_former <Generic> {
		static inline void former(argument_header<Generic>* argptr) {}

		/*template<typename HT, typename ... Tail>
		static inline void former(argument_header* argptr, const argument<HT>& head, const Tail& ... tail) {
			argptr->ptr = (void*) &head.ref;
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<HT>);
			arglist_former<Generic, Tail ...>::former(++argptr, tail ...);
		}*/

		template<typename HT, typename ... Tail>
		static inline void former(argument_header<Generic>* argptr, const argument<gxx::object_buffer<HT>>& head, const Tail& ... tail) {
			/*argptr->ptr = (void*) &head.buf;
			//dprptr(argptr->ptr);dln();
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<gxx::object_buffer<HT>>);*/
			new (argptr) argument_header<Generic>(
				(void*) &head.buf, 
				&Generic::template genfunc<gxx::object_buffer<HT>>,
				nullptr
			);
			arglist_former<Generic, Tail ...>::former(++argptr, tail ...);
		}

		/*template<typename HT, size_t N typename ... Tail>
		static inline void former(argument_header* argptr, const argument<HT(&)[N]>&& head, const Tail& ... tail) {
			argptr->ptr = (void*) &head.buf;
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<gxx::object_buffer<HT>>);
			arglist_former<Generic, Tail ...>::former(++argptr, tail ...);
		}*/
	};

	
	/*template<typename Generic, size_t N, typename HT, typename ... Tail>
	struct arglist_former<Generic, argument<HT(&)[N]>, Tail ...> {
		template<typename ... UTail>
		static inline void former(argument_header* argptr, argument<HT(&)[N]>&& head, UTail&& ... tail) {
			argptr->ptr = (void*) &head.buf;
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<gxx::object_buffer<HT>>);
			arglist_former<Generic, Tail ...>::former(++argptr, gxx::forward<UTail>(tail) ...);
		}
	};*/

	/*template<typename Generic, typename HT, typename ... Tail>
	struct arglist_former<Generic, argument<const HT*>, Tail ...> {
		template<typename ... UTail>
		static inline void former(argument_header* argptr, argument<const HT*>&& head, UTail&& ... tail) {
			argptr->ptr = (void*) &head.buf;
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<gxx::object_buffer<HT>>);
			arglist_former<Generic, Tail ...>::former(++argptr, gxx::forward<UTail>(tail) ...);
		}
	};*/

	/*template<typename Generic, typename HT, typename ... Tail>
	struct arglist_former<Generic, argument<argpair<HT>>, Tail ...> {
		static inline void former(argument_header* argptr, const argument<argpair<HT>>& head, const Tail& ... tail) {
			argptr->ptr = (void*) head.pair.body;
			argptr->name = head.pair.name;
			argptr->funcptr = (void*) (&Generic::template genfunc<HT>);
			arglist_former<Generic, Tail ...>::former(++argptr, tail ...);
		}
	};*/

	template<typename Generic>
	class arglist {
	public:
		argument_header<Generic> list[10];
	
		template<typename ... UArgs>
		explicit arglist(UArgs&& ... args) {
			//former(list, make_argument<UArgs>::doit(gxx::forward<UArgs>(args)) ...);
			arglist_former<Generic>::former(list, make_argument<UArgs>::doit(gxx::forward<UArgs>(args)) ...);
		}

		argument_header<Generic>& operator[](int i) {
			return list[i];
		}

		template<typename ... UArgs>
		int invoke(int num, UArgs&& ... args) const {
			if (num >= 10) return -1;
			//using FuncType = decltype(&Generic::template genfunc<void>);
			return list[num].funcptr(list[num].ptr, gxx::forward<UArgs>(args) ...);
		}

		int find_name(const char* name, size_t len) const {
			for(int i = 0; i < 10; ++i) {
				if (list[i].name && !strncmp(name, list[i].name, len)) return i; 
			}
			return -1;
		}
	};

	template<typename Generic, typename ... Args> 
	arglist<Generic> make_arglist(Args&& ... args) { return arglist<Generic>(gxx::forward<Args>(args) ...); } 


/*
	template<typename T> struct if_array_then_buffer { using type = T; };
	template<typename T, size_t N> struct if_array_then_buffer<T(&)[N]> { using type = gxx::object_buffer<T>; };
	

	
	
	template<typename T>
	argpair<T> arg(const char* name, const T& body) { return argpair<T>(name, body); }
	
	template<typename Generic, typename ... Tail> struct arglist_former;
	
	template<typename Generic, typename Head, typename ... Tail>
	struct arglist_former<Generic, Head, Tail...> {
		template<typename UHead, typename ... UTail>
		static inline void former(argument_header<Generic>* argptr, UHead&& head, UTail&& ... tail) {
			printf("%s\n", "Just former");
			argptr->ptr = (void*) &head;
			argptr->name = nullptr;
			argptr->array_size = -1;
			argptr->funcptr = reinterpret_cast<decltype(&Generic::template genfunc<void>)>(&Generic::template genfunc<Head>);
			arglist_former<Generic, Tail ...>::former(++argptr, tail ...);
		}
	};
	
	template<typename Generic, typename Data, size_t N, typename ... Tail>
	struct arglist_former<Generic, Data(&)[N], Tail...> {
		template<typename ... UTail>
		static inline void former(argument_header<Generic>* argptr, Data (&head) [N], UTail&& ... tail) {
			printf("%s\n", "Just array former");
			argptr->ptr = (void*) head;
			argptr->array_size = N;
			argptr->name = nullptr;
			argptr->funcptr = reinterpret_cast<decltype(&Generic::template genfunc<void>)>(&Generic::template genfunc_array<Data>);
			arglist_former<Generic, Tail ...>::former(argptr+1, tail ...);
		}
	};

	//template<typename Generic, typename Data, typename ... Tail>
	//struct arglist_former<Generic, argpair<Data>, Tail...> {
		/*static inline void former(argument_header<Generic>* argptr, const argpair<Data>& head, const Tail& ... tail) {
			argptr->ptr = (void*) &head.body;
			argptr->name = head.name;
			argptr->array_size = head.array_size;
			argptr->funcptr = reinterpret_cast<decltype(&Generic::template genfunc<void>)>(&Generic::template genfunc<Data>);
			arglist_former<Generic, Tail ...>::former(++argptr, tail ...);
		}*/
	//};
	

/*	template<typename Generic>
	struct arglist_former<Generic> {
		static void former(argument_header<Generic>* argptr) {}
	};
	
	
	
	*/
}

#endif