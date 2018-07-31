#include <gxx/trent/gbson.h>
#include <gxx/io/std.h>

//namespace gxx {
//	namespace gbson {

static int dump_numer(const gxx::trent& tr, char* buffer, size_t maxlen) { 
	long double d64 = tr.unsafe_numer_const();
	*buffer++ = (uint8_t)gxx::gbson::type::numer;
	memcpy(buffer, &d64, sizeof(d64));	
	return 1 + sizeof(long double);
}

static int dump_integer(const gxx::trent& tr, char* buffer, size_t maxlen) { 
	int64_t i64 = tr.unsafe_integer_const();
	*buffer++ = (uint8_t)gxx::gbson::type::integer;
	memcpy(buffer, &i64, sizeof(i64));	
	return 1 + sizeof(int64_t);
}

static int dump_string(const gxx::trent& tr, char* buffer, size_t maxlen) { 
	const auto& str = tr.unsafe_string_const();
	*buffer++ = (uint8_t)gxx::gbson::type::string;
	*buffer++ = (uint8_t)str.size();
	memcpy(buffer, str.data(), str.size());	
	return 2 + str.size();
}

static int dump_list(const gxx::trent& tr, char* buffer, size_t maxlen) {
	const auto& list = tr.unsafe_list_const();
	int ret = 2;

	*buffer++ = (uint8_t)gxx::gbson::type::list;
	*buffer++ = (uint8_t)list.size();	
	
	for (const auto& trent : list) {
		int lret = gxx::gbson::dump(trent, buffer, maxlen - ret); 
		if (lret < 0) return lret;
		ret += lret;
		buffer += lret;
	}
	return ret; 
}

static int dump_dict(const gxx::trent& tr, char* buffer, size_t maxlen) { 
	const auto& dict = tr.unsafe_dict_const();
	int ret = 2;

	*buffer++ = (uint8_t)gxx::gbson::type::dict;
	*buffer++ = (uint8_t)dict.size();	
	
	for (const auto& pair : dict) {
		const auto& name = pair.first;
		const auto& trent = pair.second;

		*buffer++ = (uint8_t) name.size();
		memcpy(buffer, name.data(), name.size());
		buffer += name.size();

		ret += 1 + name.size();

		int lret = gxx::gbson::dump(trent, buffer, maxlen - ret); 
		if (lret < 0) return lret;
		ret += lret;
		buffer += lret;
	}
	return ret; 
}


int gxx::gbson::dump(const gxx::trent& tr, char* buffer, size_t maxlen) {
	int ret = 0;
	gxx::trent::type type = tr.get_type();

	gxx::println(tr.type_to_str());
	switch(type) {
		case gxx::trent::type::numer: ret = dump_numer(tr, buffer, maxlen); break;
		case gxx::trent::type::integer: ret = dump_integer(tr, buffer, maxlen); break;
		case gxx::trent::type::string: ret = dump_string(tr, buffer, maxlen); break;
		case gxx::trent::type::list: ret = dump_list(tr, buffer, maxlen); break;
		case gxx::trent::type::dict: ret = dump_dict(tr, buffer, maxlen); break;
		default: return gxx::GBSON_INTERNAL_ERROR;
	}

	return ret;
}	

		/*void print_bytes(const gxx::buffer buf, gxx::io::ostream& os) {
			os.putchar(gbson_bytes_type);
			os.write((const char*)&buf.size(), 2);
			os.write(buf.data(), buf.size());		
		}

		void print_list(const gxx::trent::list_type& arr, gxx::io::ostream& os) {
			size_t sz = arr.size();
			os.putchar(gbson_list_type);
			os.write((const char*)&sz, 1);
			for (auto& v : arr) {
				dump(v, os);
			}
		}

		void print_dict(const gxx::trent::dict_type& dict, gxx::io::ostream& os) {
			size_t sz = dict.size();
			os.putchar(gbson_dict_type);
			os.write((const char*)&sz, 1);
			for (auto& d : dict) {
				print_bytes(gxx::buffer(d.first.data(), d.first.size()), os);
				dump(d.second, os);
			}
		}

		void print_numer(gxx::trent::numer_type num, gxx::io::ostream& os) {
			os.putchar(gbson_numer_type);
//            static_assert(sizeof(num) == 8);
			/*uint8_t sz;
			if
				(i64 & 0xFFFFFFFF00000000ll) sz = 8;
			else if
				(i64 & 0xFFFF0000) sz = 4;
			else if
				(i64 & 0xFF00) sz = 2;
			else
				sz = 1;
			os.putchar(sz);*/
	/*		os.write((const char*) &num, sizeof(num));
		}

		void dump(const trent& tr, gxx::io::ostream& os) {
			switch(tr.get_type()) {
				case(gxx::trent::type::numer) :
					os.putchar(gbson_numer_type);
					//os.putchar(sizeof(trent::sfloat_type));
					os.write((const char*)&tr.unsafe_numer_const(), sizeof(trent::numer_type));
					break;


				case(gxx::trent::type::string) :
					print_bytes(tr.as_buffer(), os);
					break;

				case(gxx::trent::type::list) :
					print_list(tr.unsafe_list_const(), os);
					break;

				case(gxx::trent::type::dict) :
					print_dict(tr.unsafe_dict_const(), os);
					break;
								
			}
		}

		void dump(const trent& tr, std::ostream& os) {
			gxx::io::std_ostream oss(os);
			dump(tr, oss);
		}

		result<trent> parse_numer(gxx::io::istream& is) {
			dprln("integer_type");
			uint8_t sz = 8;
			int64_t res = 0;
			is.read((char*)&res, sz);
			return res;
		}

		result<trent> parse_list(gxx::io::istream& is) {
			dprln("list_type");
			uint8_t sz = is.getchar();
			gxx::trent res(gxx::trent::type::list);
			for(int i = 0; i < sz; ++i) {
				res.unsafe_list().emplace_back(parse(is));
			}
			return res;
		}

		result<trent> parse(gxx::io::istream& is) {
			uint8_t type = is.getchar();
			
			GXX_PRINT(type);
			switch (type) {
				case gbson_numer_type:
					return parse_numer(is);

				case gbson_list_type:
					return parse_list(is);

				case gbson_dict_type:
					dprln("dict_type");
					break;
			}

			return error("gbson error");
		}

		result<trent> parse(std::istream& is) {
			gxx::io::std_istream iss(is);
			auto ret = parse(iss);
			return ret;
		}



		gxx::trent parse(const char* data, size_t size, int* sts) {
			uint8_t type = *data++;
			
			switch (type) {
				case gbson_numer_type:
					return parse_numer(is);

				case gbson_list_type:
					return parse_list(is);

				case gbson_dict_type:
					dprln("dict_type");
					break;
			}

			return ;
		}
*/	
