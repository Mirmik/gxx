#ifndef GXX_ARGLIST2_H
#define GXX_ARGLIST2_H

#include <array>
#include <assert.h>
#include <gxx/buffer.h>
#include <gxx/debug/dprint.h>

namespace gxx {
	template <typename T> class argpair; 
	struct argname {
		gxx::buffer name;
		argname(const gxx::buffer& name) : name(name) {}; 
		
		template<typename T> 
		constexpr argpair<std::remove_reference_t<T>> operator= (T&& body) { 
			return argpair<std::remove_reference_t<T>>(name, (void*)&body);
		}
	};
	
	template<typename T>
	struct argpair {
		using type = T;

		void* body;
		gxx::buffer name;

		constexpr argpair(const gxx::buffer& name, void* body) : body(body), name(name) {}
	};
	
	namespace argument_literal {
		static argname operator"" _a (const char* name, size_t sz) { 
			return argname(gxx::buffer(name, sz)); 
		} 
	}

	class visitable_argument {
	public:
		void* 		ptr;
		gxx::buffer name;
		void* 		visit;

		visitable_argument(){}
		visitable_argument(void* ptr, void* visit, const gxx::buffer& buf) : ptr(ptr), visit(visit), name(buf) {}
	};

	template<typename HT, typename ... Tail>
	static inline void visitable_arglist_former(visitable_argument* argptr, const HT& head, const Tail& ... tail) {
		new (argptr) visitable_argument( head );
		visitable_arglist_former(++argptr, tail ...);
	}

	static inline void visitable_arglist_former(visitable_argument* argptr) {
		(void) argptr;
	}

	class visitable_arglist {
	public:
		size_t N;
		visitable_argument arr[15];

		template <typename ... Args>
		visitable_arglist(Args&& ... args) : N(sizeof ... (Args)) {
			//static_assert(N == sizeof ... (Args), "Illegal arguments amount");
			visitable_arglist_former(arr, args ...);
		}

		const visitable_argument& operator[](int num) const {
			assert(num < N);
			return arr[num];
		}

		const visitable_argument& operator[](gxx::buffer str) const {
			for(uint8_t i = 0; i < N; ++i) {
				if (str == arr[i].name) return arr[i]; 
			}
			dprln("visitable_arglist: name error");
			abort();
		}
	};

	template <typename Visitor, typename Object>
	visitable_argument make_visitable_argument(Object& obj) {
		return visitable_argument((void*)&obj, Visitor::template get_visit<std::remove_const_t<std::remove_reference_t<Object>>>(), gxx::buffer());
	}
	
	template <typename Visitor, typename Object, size_t N>
	visitable_argument make_visitable_argument(Object(&obj)[N]) {
		return visitable_argument((void*)obj, Visitor::template get_visit<std::remove_const_t<std::remove_reference_t<Object*>>>(), gxx::buffer());
	}

	template <typename Visitor, typename Object>
	visitable_argument make_visitable_argument(Object*& obj) {
		return visitable_argument((void*)obj, Visitor::template get_visit<std::remove_const_t<std::remove_reference_t<Object*>>>(), gxx::buffer());
	}
	
	template <typename Visitor, typename Object>
	visitable_argument make_visitable_argument(argpair<Object>& pair) {
		return visitable_argument(pair.body, Visitor::template get_visit<std::remove_const_t<std::remove_reference_t<Object>>>(), pair.name);
	}
	
	template <typename Visitor, typename Object, size_t N>
	visitable_argument make_visitable_argument(argpair<Object[N]>& pair) {
		return visitable_argument(pair.body, Visitor::template get_visit<std::remove_const_t<std::remove_reference_t<Object*>>>(), pair.name);
	}

	template <typename Visitor, typename Object>
	visitable_argument make_visitable_argument(argpair<Object*>& pair) {
		return visitable_argument(*(void**)pair.body, Visitor::template get_visit<std::remove_const_t<std::remove_reference_t<Object*>>>(), pair.name);
	}

	////////////////////////////////////////////////	
	template <typename Visitor, typename ... Args>
	visitable_arglist make_visitable_arglist(Args&& ... args) {
		return visitable_arglist(make_visitable_argument<Visitor>(args) ...);
	}
}

#define GXX_REGISTER_ARGUMENT_VISITOR(visitor, ...) struct visitor {		\
	template<typename Object> static void* get_visit();						\
	using ftype = __VA_ARGS__;												\
																			\
	template<typename ... Args>												\
	static auto visit(gxx::visitable_argument varg, Args&& ... args) {		\
		ftype fptr = (ftype) varg.visit;									\
		return fptr(varg.ptr, std::forward<Args>(args) ...);				\
	}																		\
};

#define GXX_REGISTER_ARGUMENT_VISIT(visitor, type, func) namespace gxx { template<> void* visitor::get_visit<type>() { return (void*)&func; } }

#endif
