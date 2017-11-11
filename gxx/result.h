#ifndef GXX_RESULT_H
#define GXX_RESULT_H

#include <cstdlib>
#include <cassert>
#include <string>
#include <functional>
#include <utility>
#include <string.h>

#include <gxx/debug/dprint.h>

namespace gxx { namespace result_type {
	struct exception {
		virtual const char* what() = 0;
	};

	struct error : public exception {
		//std::string info;
		char* info;
		explicit error() : info() {}
		explicit error(const char* str) : info(strdup(str)) {}
		explicit error(const std::string& str) : info((char*) str.c_str()) {}
		
		error(error&& e) = default;		
		error& operator=(error&& other) = default;

		~error() {
			free(info);
		};

		const char* what() {
			return info;
		}
	};
	
	template<typename T> 
	struct tryhelper {
		using type = T;
		using storedtype = T;
		template <typename Arg>
		static void constructor(type& ths, Arg oth) {
			new (&ths) type(std::forward<Arg>(oth));
		}
		static void destructor(type& ths) {ths.~type();};
		static void constructor(type& ths) {
			new (&ths) type();
		};
	};
	
	template<typename T> 
	struct tryhelper<T&> {
		using type = T&;
		using storedtype = std::reference_wrapper<T>;
		template <typename Arg>
		static void constructor(storedtype& ths, Arg oth) {
			new (&ths) storedtype(oth);	
		}
		static void destructor(storedtype& ths) {ths.~storedtype();};
		static void constructor(storedtype& ths) {};
	};
	
	template<typename T> 
	struct tryhelper<T&&> {
		using type = T&&;
		using storedtype = T&&;
		template <typename Arg>
		static void constructor(type& ths, Arg oth) {	
			ths = oth;
		}
		static void destructor(type& ths) {};
		static void constructor(type& ths) {};
	};

	template <typename T, typename E = error>
	class result {
	public:
		using Stored = typename tryhelper<T>::storedtype;
		using Result =typename tryhelper<T>::type;
		uint8_t _iserror;
		union {
			Stored _data;
			E _error;
		};
	
	public:
		
		template<typename U>
		result(U&& r) :	_iserror(false), _data(std::forward<U>(r)) {}
		result(E&& e) : _iserror(true), _error(std::forward<E>(e)) {}
		result(E& e) : _iserror(true), _error(e) {}
		
		result(result&& res) : _iserror(res._iserror) {
			if (_iserror) {
				new (&_error) E(std::move(res._error));
			} else { 
				tryhelper<T>::constructor(_data, std::move(res._data));
			}; 
			_iserror = 2;
		}
		
		~result() {
			switch (_iserror) {
				case 1: _error.~E(); break;
				case 0: tryhelper<T>::destructor(_data); break;
				default: break;	
			};		
		}
	
		Result& unwrap() {
			if (is_error()) { 
				dpr("unwrap error: ");
				dprln(_error.what());
				abort();
			}
			return _data;
		}

		inline void restore(T&& r) {
			_iserror = false;
			_error.~error();
			_data = std::forward<T>(r);	
		}
	
		Result& getData() {
			assert(_iserror == 0);
			return _data;
		}
		
		E& getError() {
			assert(_iserror == 1);
			return _error;
		}
		
		bool is_error() {
			return _iserror;
		}

		operator T() {
			assert(_iserror == 0);
			return _data;
		}

		inline void restore() {
			assert(_iserror == 1);
			_iserror = false;
			_error.~error();
			tryhelper<T>::constructor(_data);	
		}
	};

	template <typename E>
	struct result<void, E> {
		using Result = void;
		uint8_t _iserror;
		union {
			E _error;
		};
		
		result() : _iserror(false) {}
		result(E&& e) : _iserror(true), _error(std::move(e)) {}
		result(E& e) : _iserror(true), _error(e) {}
		
		result(result&& res) : _iserror(res._iserror) {
			if (_iserror) {
				new (&_error) E(std::move(res._error));
			} else { }; 
			_iserror = 2;
		}
		
		~result() {
			switch (_iserror) {
				case 1: _error.~E(); break;
				default: break;	
			};		
		}
	
		void unwrap() {
			if (is_error()) { 
				dpr("unwrap error: ");
				abort_dprln(_error.what());
			}
		}

		void getData() {
			assert(_iserror == 0);
		}
		
		E& getError() {
			assert(_iserror == 1);
			return _error;
		}
		
		bool is_error() {
			return _iserror;
		}

		inline void restore() {
			assert(_iserror == 1);
			_iserror = false;
			_error.~error();
		}
	
		operator bool() {
			return _iserror;
		}
	};
}}

#define tryS(invoke) ({												\
	auto&& __result = ({invoke;}); 									\
	if (__result.is_error()) return std::move(__result.getError());	\
	__result.getData();												\
}) 

#define tryH(invoke,err,handler) ({									\
	__label__ try_label;											\
	auto&& __result = ({invoke;});									\
	if (__result.is_error()) {										\
		auto& err = __result.getError(); 							\
		handler; 													\
		return std::move(__result.getError());						\
	}; 																\
	try_label:														\
	__result.getData();												\
})

#define tryP(invoke,err,handler) ({									\
	__label__ try_label;											\
	auto&& __result = ({invoke;});									\
	if (__result.is_error()) {										\
		auto& err = __result.getError(); 							\
		handler; 													\
		__result.restore();											\
	}; 																\
	try_label:														\
	__result.getData();												\
})

#define try_restore(val) ({__result.restore(val); goto try_label;})

#endif
