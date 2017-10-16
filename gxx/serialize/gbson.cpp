#include <gxx/serialize/gbson.h>

namespace gxx {
	namespace gbson {
        constexpr unsigned char gbson_integer_type = 0;
		constexpr unsigned char gbson_float_type = 2;
		constexpr unsigned char gbson_bytes_type = 3;
		constexpr unsigned char gbson_array_type = 4;
		constexpr unsigned char gbson_dictionary_type = 5;
        constexpr unsigned char gbson_boolean_type = 6;
		
        void print_bytes(const gxx::buffer buf, gxx::io::ostream& os) {
			os.putchar(gbson_bytes_type);
            os.write((const char*)&buf.size(), 2);
			os.write(buf.data(), buf.size());		
		}

        void print_array(const gxx::trent::array_type& arr, gxx::io::ostream& os) {
            size_t sz = arr.size();
            os.putchar(gbson_array_type);
            os.write((const char*)&sz, 2);
            for (auto& v : arr) {
                print_to(v, os);
            }
        }

        void print_dictionary(const gxx::trent::dictionary_type& dict, gxx::io::ostream& os) {
            size_t sz = dict.size();
            os.putchar(gbson_dictionary_type);
            os.write((const char*)&sz, 2);
            for (auto& d : dict) {
                print_bytes(gxx::buffer(d.first), os);
                print_to(d.second, os);
            }
        }

		void print_to(const trent& tr, gxx::io::ostream& os) {
            switch(tr.get_type()) {
                case(gxx::trent::type::floating) :
					os.putchar(gbson_float_type);
					os.putchar(sizeof(trent::float_type));
                    os.write((const char*)&tr.unsafe_float_const(), sizeof(trent::float_type));
					break;

                case(gxx::trent::type::integer) :
                    os.putchar(gbson_integer_type);
                    os.putchar(sizeof(trent::integer_type));
                    os.write((const char*)&tr.unsafe_integer_const(), sizeof(trent::integer_type));
                    break;

                case(gxx::trent::type::string) :
                    print_bytes(tr.as_buffer(), os);
					break;

                case(gxx::trent::type::array) :
                    print_array(tr.unsafe_array_const(), os);
                    break;

                case(gxx::trent::type::dictionary) :
                    print_dictionary(tr.unsafe_dictionary_const(), os);
					break;
								
			}
		}
	}
}
