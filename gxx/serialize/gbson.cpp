#include <gxx/serialize/gbson.h>

namespace gxx {
    namespace gbson {
		
        void print_bytes(const gxx::buffer buf, gxx::io::ostream& os) {
			os.putchar(gbson_bytes_type);
            os.write((const char*)&buf.size(), 2);
			os.write(buf.data(), buf.size());		
		}

        void print_array(const gxx::trent::array_type& arr, gxx::io::ostream& os) {
            size_t sz = arr.size();
            os.putchar(gbson_array_type);
            os.write((const char*)&sz, 1);
            for (auto& v : arr) {
                dump(v, os);
            }
        }

        void print_dictionary(const gxx::trent::dictionary_type& dict, gxx::io::ostream& os) {
            size_t sz = dict.size();
            os.putchar(gbson_dictionary_type);
            os.write((const char*)&sz, 1);
            for (auto& d : dict) {
                print_bytes(gxx::buffer(d.first.data(), d.first.size()), os);
                dump(d.second, os);
            }
        }

        void print_integer(int64_t i64, gxx::io::ostream& os) {
            os.putchar(gbson_integer_type);
            uint8_t sz;
            if
                (i64 & 0xFFFFFFFF00000000ll) sz = 8;
            else if
                (i64 & 0xFFFF0000) sz = 4;
            else if
                (i64 & 0xFF00) sz = 2;
            else
                sz = 1;
            os.putchar(sz);
            os.write((const char*) &i64, sz);
        }

        void dump(const trent& tr, gxx::io::ostream& os) {
            switch(tr.get_type()) {
                case(gxx::trent::type::single_floating) :
                    os.putchar(gbson_float_type);
                    os.putchar(sizeof(trent::sfloat_type));
                    os.write((const char*)&tr.unsafe_sfloat_const(), sizeof(trent::sfloat_type));
					break;


                case(gxx::trent::type::double_floating) :
                    os.putchar(gbson_float_type);
                    os.putchar(sizeof(trent::dfloat_type));
                    os.write((const char*)&tr.unsafe_dfloat_const(), sizeof(trent::dfloat_type));
                    break;

                case(gxx::trent::type::integer) :
                    print_integer(tr.unsafe_integer_const(), os);
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

        result<trent> parse_integer(gxx::io::istream& is) {
            dprln("integer_type");
            uint8_t sz = is.getchar();
            int64_t res = 0;
            is.read((char*)&res, sz);
            return res;
        }

        result<trent> parse_array(gxx::io::istream& is) {
            dprln("array_type");
            uint8_t sz = is.getchar();
            gxx::trent res(gxx::trent::type::array);
            for(int i = 0; i < sz; ++i) {
                res.unsafe_array().emplace_back(parse(is));
            }
            return res;
        }

        result<trent> parse(gxx::io::istream& is) {
            uint8_t type = is.getchar();

            switch (type) {
                case gbson_integer_type:
                    return parse_integer(is);

                case gbson_float_type:
                    dprln("float_type");
                    break;

                case gbson_array_type:
                    return parse_array(is);

                case gbson_dictionary_type:
                    dprln("dictionary_type");
                    break;
            }

            return error("gbson error");
        }
	}
}
