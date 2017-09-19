#ifndef GXX_PATH_PATH_H
#define GXX_PATH_PATH_H

#include <gxx/string.h>
#include <gxx/io/printable.h>

namespace gxx {
	namespace path {
		class path : public gxx::io::printable {
		protected:
			std::string raw;

		public:
			path(std::string str) : raw(str) {};
	
			bool is_exist();

			size_t printTo(gxx::io::ostream& o) const override {
				//int ret = o.print(raw);
				//return ret;
			}
		};
	}
}

#endif
