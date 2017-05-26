#ifndef GXX_ARGSLIST_H
#define GXX_ARGSLIST_H

#include <gxx/buffer.h>
#include <gxx/utility.h>

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
		T& ref;
	//public:
		template<typename U>
		constexpr argument(U&& ref) : ref(ref) {
			printf("Just arg\n");
		}
	};

	template<typename T>
	struct argument<argpair<T>> {
		argpair<T>& pair;
	//public:
		template<typename U>
		constexpr argument(U&& ref) : pair(ref) {
			printf("Just argpair\n");
		}
	};

	template<typename T, size_t N>
	struct argument<T(&)[N]> {
		gxx::object_buffer<T> buf;
	//public:
		constexpr argument(T(&arr)[N]) : buf(arr) {
			printf("Just array\n");
		}
	};

	namespace literals {
		argname operator"" _a (const char* name, size_t sz) { return argname(name); } 
	}

	struct argument_header {
		void* ptr;
		void* funcptr;
		const char* name;
		
		//DEBUG
		void debug_print() {
			std::cout << ptr << '\t' << funcptr << std::endl;
			if (name) std::cout << name << std::endl;
		}
	};


	template<typename Generic, typename ... Tail> struct arglist_former;

	template<typename Generic> struct arglist_former <Generic> {
		static inline void former(argument_header* argptr) {}
	};

	template<typename Generic, typename HT, typename ... Tail>
	struct arglist_former<Generic, argument<HT>, Tail ...> {
		template<typename ... UTail>
		static inline void former(argument_header* argptr, argument<HT>&& head, UTail&& ... tail) {
			printf("%s\n", "Just former");
			argptr->ptr = (void*) &head.ref;
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<HT>);
			arglist_former<Generic, Tail ...>::former(++argptr, gxx::forward<UTail>(tail) ...);
		}
	};

	template<typename Generic, size_t N, typename HT, typename ... Tail>
	struct arglist_former<Generic, argument<HT(&)[N]>, Tail ...> {
		template<typename ... UTail>
		static inline void former(argument_header* argptr, argument<HT(&)[N]>&& head, UTail&& ... tail) {
			printf("%s\n", "Array former");
			argptr->ptr = (void*) &head.buf;
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<gxx::object_buffer<HT>>);
			arglist_former<Generic, Tail ...>::former(++argptr, gxx::forward<UTail>(tail) ...);
		}
	};

	template<typename Generic, typename HT, typename ... Tail>
	struct arglist_former<Generic, argument<argpair<HT>>, Tail ...> {
		template<typename ... UTail>
		static inline void former(argument_header* argptr, argument<argpair<HT>>&& head, UTail&& ... tail) {
			printf("%s\n", "Just pair");
			argptr->ptr = (void*) head.pair.body;
			argptr->name = nullptr;
			argptr->funcptr = (void*) (&Generic::template genfunc<HT>);
			arglist_former<Generic, Tail ...>::former(++argptr, gxx::forward<UTail>(tail) ...);
		}
	};

	template<typename Generic, typename ... Args>
	class arglist {
	public:
		argument_header list[sizeof...(Args)];
	
		template<typename ... UArgs>
		arglist(UArgs&& ... args) {
			arglist_former<Generic, UArgs ...>::former(list, gxx::forward<UArgs>(args) ...);
		}

		argument_header& operator[](int i) {
			return list[i];
		}

		template<typename ... UArgs>
		int invoke(int num, UArgs&& ... args) {
			using FuncType = decltype(&Generic::template genfunc<void>);
			return ((FuncType)(list[num].funcptr))(list[num].ptr, gxx::forward<UArgs>(args) ...);
		}


	};

	template<typename Generic, typename ... Args> 
	arglist<Generic, Args...> make_arglist(Args&& ... args) { return arglist<Generic, Args ...>(gxx::forward<Args>(args) ...); } 


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