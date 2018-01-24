#ifndef GXX_TRENT_CHECKER_H
#define GXX_TRENT_CHECKER_H

#include <gxx/util/string.h>
#include <gxx/trent/trent.h>
#include <gxx/result.h>

using namespace gxx::result_type;

namespace gxx { 

	class schema {
	public:
		enum checker_type {
                        dict_checker_type,
                        list_checker_type,
			string_checker_type,
			numer_checker_type,
		};


		class schema_node {
			checker_type type;

		public:
			schema_node(checker_type type) : type(type) {}

			result<void> check(const trent& tr, gxx::strvec& strvec) const {
				switch(type) {
                                        case dict_checker_type:
                                                if (!tr.is_dict()) return error("should be dictionary");
						break;
                                        case list_checker_type:
                                                if (!tr.is_list()) return error("should be list");
                                                if (len != -1 && tr.as_list().size() != len) return error(gxx::format("array size should be {}", len));
						break;
					case string_checker_type: 
						if (!tr.is_string()) return error("should be string"); 
						break;
					case numer_checker_type: 
						if (!tr.is_numer()) return error("should be numer"); 
						break;
					default:
						PANIC_TRACED();
				}

                                if (type == dict_checker_type) {
					for (const auto& n : nodes) {
						strvec.push_back(n.first);
						if (!tr.have(n.first)) return error("isn't exist");
						tryS(n.second.check(tr[n.first], strvec));
						strvec.pop_back();
					}
				}

				return result<void>();
			}

			schema_node& length(int n) {
				len = n;
				return *this;
			}

			std::map<std::string, schema_node> nodes; 
			int len = -1;
			schema_node& operator[](std::string str) { return nodes.at(str); }
		};

		struct schema_dict_pair {
			std::string str;
			schema_node node;			
		};

                struct dict : public schema_node {
                    dict(const std::initializer_list<schema_dict_pair>& lst) : schema_node(dict_checker_type) {
			for (const auto& l : lst) {
                                nodes.insert(std::make_pair(l.str, l.node));
                        }
                    }
                };

                struct list : public schema_node {
                    list() : schema_node(list_checker_type) {}
                };

                struct string : public schema_node {
                    string() : schema_node(string_checker_type) {}
                };

                struct numer : public schema_node {
                    numer() : schema_node(numer_checker_type) {}
                };

		void asserted_check(const trent& tr, std::string rootname) {
			std::vector<std::string> strvec { rootname };
			auto ret = root.check(tr, strvec);
			if (ret.is_error()) {
				std::string path = gxx::join(strvec, '/');
				std::string errtxt = gxx::format("SCHEMA: trent {} {}", path, ret.getError().what());
				gxx::panic(errtxt.c_str());
			}
		}

		schema_node root;
		schema(const schema_node& root) : root(root) {}
	};
}

#endif
