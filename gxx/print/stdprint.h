#ifndef GXX_STD_PRINT_H
#define GXX_STD_PRINT_H

#include <gxx/print.h>
#include <gxx/container/dlist.h>

#include <array>
#include <vector>
#include <map>
#include <set>
#include <list>

//#include <typeinfo>

namespace gxx
{
	template<typename T>
	size_t print_array_like_to(gxx::io::ostream& o, const T& arr)
	{
		ssize_t ret = 0;
		ret += o.putchar('[');
		size_t s = arr.size();
		for (const auto& g : arr)
		{
			ret += gxx::print_to(o, g);
			if (--s) ret += o.putchar(',');
		}
		ret += o.putchar(']');

		return ret;
	}

	template<typename T, typename A>
	struct print_functions<std::vector<T, A>>
	{
		static ssize_t print(gxx::io::ostream& o, std::vector<T, A> const& vec)
		{
			return print_array_like_to(o, vec);
		}
	};

	template<typename T, typename A>
	struct print_functions<std::set<T, A>>
	{
		static ssize_t print(gxx::io::ostream& o, std::set<T, A> const& vec)
		{
			return print_array_like_to(o, vec);
		}
	};

	template<typename T, typename A>
	struct print_functions<std::list<T, A>>
	{
		static ssize_t print(gxx::io::ostream& o, std::list<T, A> const& vec)
		{
			return print_array_like_to(o, vec);
		}
	};

	template<typename T, dlist_head T::* L>
	struct print_functions<gxx::dlist<T, L>>
	{
		static ssize_t print(gxx::io::ostream& o, gxx::dlist<T, L> const& vec)
		{
			return print_array_like_to(o, vec);
		}
	};

	template<typename T, size_t N>
	struct print_functions<std::array<T, N>>
	{
		static ssize_t print(gxx::io::ostream& o, std::array<T, N> const& vec)
		{
			return print_array_like_to(o, vec);
		}
	};

	//template<typename T>
	//struct print_functions<std::set<T>> {
	//	static ssize_t print(gxx::io::ostream& o, std::set<T> const& vec) {
	//		return print_array_like_to(o, vec);
	//	}
	//};

	template<typename T, typename K>
	struct print_functions<std::map<K, T>>
	{
		static ssize_t print(gxx::io::ostream& o, std::map<K, T> const& dict)
		{
			ssize_t ret = 0;

			ret += o.putchar('{');
			if (dict.size() != 0)
			{
				auto it = dict.begin();
				auto end = dict.end();

				ret += gxx::print_to(o, (*it).first);
				ret += o.putchar(':');
				ret += gxx::print_to(o, (*it).second);
				it++;
				while (it != end)
				{
					ret += o.putchar(',');
					ret += gxx::print_to(o, (*it).first);
					ret += o.putchar(':');
					ret += gxx::print_to(o, (*it).second);
					it++;
				}
			}
			ret += o.putchar('}');
			
			return ret;
		}
	};

	template<>
	struct print_functions<std::string>
	{
		static ssize_t print(gxx::io::ostream& o, const std::string& str)
		{
			return o.print(str.c_str());
		}
	};

	/*template<>
	struct fprint_functions<std::string>
	{
		static ssize_t format_print(const std::string& obj, gxx::io::ostream& o, gxx::buffer opt)
		{
			return o.format_print(obj.c_str(), obj.size(), opt);
		}
	};*/

	template<typename T0, typename T1>
	struct print_functions<std::pair<T0, T1>>
	{
		static ssize_t print(gxx::io::ostream& o, std::pair<T0, T1> const& pr)
		{
			ssize_t ret = 0;

			ret += o.putchar('(');
			ret += gxx::print_to(o, pr.first);
			ret += o.putchar(',');
			ret += gxx::print_to(o, pr.second);
			ret += o.putchar(')');

			return ret;
		}
	};

	/*template<>
	struct print_functions<std::type_info> {
		static ssize_t print(gxx::io::ostream& o, std::type_info const& info) {
			return gxx::print_to(o, info.name());
		}
	};*/
}


#endif
