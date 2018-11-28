#ifndef GXX_ARGLIST2_H
#define GXX_ARGLIST2_H

//Структура данных visitable_arglist используется для форматирующей печати.
//Для обработки строки формата все аргументы однотипно записываются с помощью указателей,
//указатели их обработчиков также сохраняются, тем самым осуществляя сохранение типа.
//За подбор обработчиков отвечает класс визитёр (Visitor). Он же ответственен за вызов.
//Таким образом visitable_arglist - это средство разграничения во времени многоаргументного
//вызова и его исполнения.

#include <memory>
#include <utility>
#include <assert.h>
#include <gxx/buffer.h>
#include <gxx/panic.h>

namespace gxx
{
	namespace detail
	{
		template<typename T> struct va_remove_cvref
		{
			typedef typename std::remove_volatile <
			typename std::remove_const <
			typename std::remove_reference<T>
			::type >::type >::type type;
		};
		template<typename T> using va_remove_cvref_t = typename va_remove_cvref<T>::type;
	}

	/**
	 *	Класс именованного аргумента.
	 *  Является шаблонным классом, чтобы доставить информацию о типе аргумента
	 *  в конструктор visitable_argument.
	 */
	template<typename T>
	struct argpair
	{
		void* body;
		gxx::buffer name;
		constexpr argpair(const gxx::buffer& _name, const T& _body) : body((void*)&_body), name(_name) {}
	};

	/**
	 *	Класс имени аргумента, используется как временный объект,
	 *  порождающий объект именованного аргумента argpair. 
	 */
	struct argname
	{
		gxx::buffer name;
		constexpr argname(const gxx::buffer& _name) : name(_name) {};

		template<typename T>
		constexpr argpair<T> operator= (const T& body)
		{
			return argpair<T>(name, body);
		}
	};

	namespace argument_literal
	{
		static inline argname operator"" _a (const char* name, size_t sz)
		{
			return argname(gxx::buffer(name, sz));
		}
	}

	/**
	 *	visitable_argument
	 *	Хранит данные об указатели, имени и точке доступа к визитёру.
	 *	Используется для хранения в упорядоченном массиве информации об аргументах функции.
	 */
	struct visitable_argument
	{
		void* 		ptr;
		gxx::buffer name;
		void* 		visit;

		visitable_argument(void* _ptr, const gxx::buffer& buf, void* _visit) : 
			ptr(_ptr), name(buf), visit(_visit) {}

		template <typename Visitor, typename Object>
		visitable_argument(const Object& obj, const Visitor& visitor)
			: visitable_argument(
			      (void*) & obj,
			      gxx::buffer(),
			      Visitor::template get_visit<detail::va_remove_cvref_t<Object>>())
		{}

		template <typename Visitor, typename Object>
		visitable_argument(const argpair<Object>& pair, const Visitor& visitor)
			: visitable_argument(
			      pair.body,
			      pair.name,
			      Visitor::template get_visit<detail::va_remove_cvref_t<Object>>())
		{}
	};

	/**
	 *	visitable_arglist
	 *	Предоставляет интерфейс доступа к массиву visitable_argument.
	 *
	 *  @buffer - буфер данных, передаваемый извне для нужд хранения. Должен иметь длину
	 * 	не менее количества аргуметов.
	 */
	class visitable_arglist
	{
		size_t N;
		visitable_argument* arr;

	public:
		visitable_arglist() : N(0), arr(nullptr) {}

		__attribute__((deprecated))
		visitable_arglist(visitable_argument* buffer, size_t N) : N(N), arr(buffer) {}

		template<size_t M>
		visitable_arglist(visitable_argument(&& arr)[M]) 
			: N(M), arr(arr) 
		{}

		visitable_argument* begin()
		{
			return arr;
		}

		visitable_argument* end()
		{
			return arr + N;
		}

		const visitable_argument& operator[](size_t num) const
		{
			assert(num < N);
			return arr[num];
		}

		const visitable_argument& operator[](gxx::buffer str) const
		{
			for (uint8_t i = 0; i < N; ++i)
			{
				if (str == arr[i].name) return arr[i];
			}

			gxx::panic("visitable_arglist: name error");
			return arr[0]; // -Wreturn-type
		}
	};
}

#endif
