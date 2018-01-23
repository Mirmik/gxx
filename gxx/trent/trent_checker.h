#ifndef GXX_TRENT_CHECKER_H
#define GXX_TRENT_CHECKER_H

#include <gxx/trent/trent.h>
#include <gxx/result.h>

using namespace gxx::result_type;

namespace gxx { 

	class schema {
	public:
		enum checker_type {
			dictionary_checker_type,
			array_checker_type,
			string_checker_type,
			numer_checker_type,
		};


		class schema_node {
			checker_type type;

		public:
			schema_node(checker_type type) : type(type) {}

			result<void> check(const trent& tr) {
				switch(type) {
					case dictionary_checker_type: if (!tr.is_dictionary()) return error("{} should be dictionary"); break;
					case array_checker_type: if (!tr.is_dictionary()) return error("{} should be list"); break;
					case string_checker_type: if (!tr.is_dictionary()) return error("{} should be string"); break;
					case numer_checker_type: if (!tr.is_dictionary()) return error("{} should be numer"); break;
				}
			}

			std::map<std::string, schema_node> nodes; 
			schema_node& operator[](std::string str) { return nodes.at(str); }
		};

		struct schema_dict_pair {
			std::string str;
			schema_node node;			
		};

		static auto dict(const std::initializer_list<schema_dict_pair>& lst) {
			auto ret = schema_node(dictionary_checker_type);
			for (const auto& l : lst) {
				ret.nodes.insert(std::make_pair(l.str, l.node));
			}
			return ret;
		}

		static auto array() {
			return schema_node(dictionary_checker_type);
		}

		static auto string() {
			return schema_node(string_checker_type);
		}

		

		schema_node root;
		schema(const schema_node& root) : root(root) {}
	};
}

#endif