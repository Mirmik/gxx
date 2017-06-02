#ifndef GXX_JSON_SETTINGS_H
#define GXX_JSON_SETTINGS_H

#include <gxx/serialize/json_parser.h>
#include <gxx/io/stdstream.h>

namespace gxx {

	class json_settings {
	public:
		json root;
		gxx::string pathstr;
		std_fstream file;

		json_settings(const char* path) : file(path), pathstr(path) {};

		void load() {
			root = json_parser::parse(text_reader(file)).unwrap();

			std_fstream file2(pathstr.c_str());
			root.prettyPrintTo(text_writer(file2));
		}


	};

}

#endif