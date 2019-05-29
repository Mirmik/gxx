#ifndef GXX_UTIL_PRINT_H
#define GXX_UTIL_PRINT_H

//Функции печати задаются с помощью специализации шаблонов структур для того, чтобы их можно было
//подтягивать по всей программе.
#include <gxx/io/ostream.h>
#include <gxx/util/booltype.h>

#include <gxx/panic.h>
#include <iostream>

#if 0
#define PRINT_VISITOR_DTRACE() DTRACE()
#else
#define PRINT_VISITOR_DTRACE()
#endif

namespace gxx
{
	namespace io { class ostream; }

	template <typename T, typename U = int>
	struct is_have_fmtPrintTo : gxx::false_type { };

	template <typename T>
	struct is_have_fmtPrintTo <T, decltype((void) &T::fmtPrintTo, 0)> : gxx::true_type { };

	template <typename T, typename U = int>
	struct is_have_printTo : gxx::false_type { };

	template <typename T>
	struct is_have_printTo <T, decltype((void) &T::printTo, 0)> : gxx::true_type { };


	namespace detail
	{
		template <typename>
		struct sfinae_true : std::true_type
		{ };

		/*template <typename T> static auto test_stream(int)
		    -> sfinae_true<decltype(std::declval<std::ostream &>() << std::declval<T>())>;
		template <typename T> static auto test_stream(...) -> std::false_type;*/

		template <typename T> static auto test_gxxout(int)
		    -> sfinae_true<decltype(std::declval<io::ostream &>().format_print(std::declval<T>(), gxx::buffer()))>;
		template <typename T> static auto test_gxxout(...) -> std::false_type;
	}

	//template <typename T> struct has_output_operator : decltype(detail::test_stream<T>(0)) { };
	template <typename T> struct has_native_format_print : decltype(detail::test_gxxout<T>(0)) { };

	/*struct sfinae_base
	{
		typedef char yes[1];
		typedef char no[2];
	};

	template<typename T>
	struct has_insertion_operator : sfinae_base
	{

		// this may quietly fail:
		template<typename U> static yes& test(
		    size_t (*n)[ sizeof( std::cout << * static_cast<U*>(0) ) ] );

		// "..." provides fallback in case above fails
		template<typename U> static no& test(...);

		constexpr static bool const value = sizeof( test<T>( NULL ) ) == sizeof( yes );
	};*/

	template<typename T, bool HavePrintTo = true>
	struct print_functions_basic
	{
		static ssize_t print(gxx::io::ostream& o, const T& obj)
		{
			PRINT_VISITOR_DTRACE();
			return obj.printTo(o);
		}
	};

	template<typename T>
	struct print_functions_basic<T, false>
	{
		static ssize_t print(gxx::io::ostream& o, const T& obj)
		{
			PRINT_VISITOR_DTRACE();
			return o.print(obj);
		};
	};

	/*template<typename T>
	struct print_functions_basic<T, true, false>
	{
		static ssize_t print(gxx::io::ostream& o, const T& obj)
		{
			dprln("TODO: make ostream adapter");
			PANIC_TRACED();
			return 0;
		};
	};*/

	template<typename T>
	struct print_functions : public print_functions_basic<T, is_have_printTo<T>::value> {};

	
	
	template<typename T, bool NativeFormated, bool HaveFmtPrintTo = true>
	struct fprint_functions_basic
	{
		static ssize_t format_print(const T& obj, gxx::io::ostream& o, gxx::buffer opt)
		{
			return obj.fmtPrintTo(o, opt);
		};
	};
	
	template<typename T>
	struct fprint_functions_basic<T, true, false>
	{
		static ssize_t format_print(const T& obj, gxx::io::ostream& o, gxx::buffer opt)
		{
			return o.format_print(obj, opt);
		}
	};

	template<typename T>
	struct fprint_functions_basic<T, false, false>
	{
		static ssize_t format_print(const T& obj, gxx::io::ostream& o, gxx::buffer opt)
		{
			return gxx::print_functions<T>::print(o, obj);
		}
	};


	/*
	template<typename T, bool Printable = true>
	struct fprint_functions_basic
	{
		static ssize_t format_print(const T& obj, gxx::io::ostream& o, gxx::buffer opt)
		{

			PRINT_VISITOR_DTRACE();
			(void) opt;
			return gxx::print_functions<T>::print(o, obj);
			//return obj.fmtPrintTo(o, opt);
		};
	};

	template<>
	struct fprint_functions_basic<char*, false>
	{
		static ssize_t format_print(char* obj, gxx::io::ostream& o, gxx::buffer opt)
		{
			(void) opt;
			//return gxx::print_functions<T>::print(o, obj);
			return o.format_print(obj, opt);
		}
	};

	template<typename T>
	struct fprint_functions_basic<T, false>
	{
		static ssize_t format_print(const T& obj, gxx::io::ostream& o, gxx::buffer opt)
		{
			PRINT_VISITOR_DTRACE();
			(void) opt;
			return gxx::print_functions<T>::print(o, obj);
			//return o.format_print(obj, opt);
		}
	};*/

	template<typename T>
	struct fprint_functions : public fprint_functions_basic<T, 
		has_native_format_print<T>::value,
		is_have_fmtPrintTo<T>::value
	> {};
}

#endif
