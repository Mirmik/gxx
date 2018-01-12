#ifndef GXX_STD_PRINT_H
#define GXX_STD_PRINT_H

#include <gxx/print.h>
#include <array>
#include <vector>
#include <map>
#include <set>

namespace gxx {
	template<typename T, typename A> 
	struct print_functions<std::vector<T,A>> {
		static int print(gxx::io::ostream& o, std::vector<T,A> const& vec) {
			o.putchar('[');
						if (vec.size() != 0) {
							for (int i = 0; i < vec.size() - 1; ++i) {
									gxx::print_to(o, vec[i]);
									o.putchar(',');
							}
							gxx::print_to(o, vec[vec.size() - 1]);
						}
			o.putchar(']');
		}
	};

	template<typename T, typename A> 
	struct print_functions<std::set<T,A>> {
		static int print(gxx::io::ostream& o, std::set<T,A> const& vec) {
			o.putchar('[');
			int s = vec.size();
			for (const auto& g : vec) {
				gxx::print_to(o, g);
				if (--s) o.putchar(' ');
			}
			o.putchar(']');
		}
	};

	template<typename T, size_t N> 
	struct print_functions<std::array<T,N>> {
		static int print(gxx::io::ostream& o, std::array<T,N> const& vec) {
			o.putchar('[');
			for (int i = 0; i < N - 1; ++i) {
				gxx::print_to(o, vec[i]);
				o.putchar(',');
			}
			if (N != 0)
				gxx::print_to(o, vec[N - 1]);
			o.putchar(']');
		}		
	};

	template<typename T, typename K>  
	struct print_functions<std::map<K,T>> {
		static int print(gxx::io::ostream& o, std::map<K,T> const& dict) {
			o.putchar('{');
			if (dict.size() != 0) {
				auto it = dict.begin();
				auto end = dict.end();

				gxx::print_to(o, (*it).first); o.putchar(':'); gxx::print_to(o, (*it).second);
				it++;
				while(it != end) {
					o.putchar(',');
					gxx::print_to(o, (*it).first); o.putchar(':'); gxx::print_to(o, (*it).second);	
					it++;
				}
			} 
			o.putchar('}');
		}
	};

	template<> 
	struct print_functions<std::string> {
		static int print(gxx::io::ostream& o, const std::string& str) {
				o.print(str.c_str());
		}
	};
}


#endif
