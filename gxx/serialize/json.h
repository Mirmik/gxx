#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <ostream>
#include <gxx/serialize/datatree.h>

namespace gxx {
	class json : public datatree {
	public:
		template<typename ... Args> 
		json(Args ... args) : datatree(std::forward<Args>(args) ...) {}

		public:
		void printTo(std::ostream& os);
		void prettyPrintTo(std::ostream& os, int tab = 0);
	};
}

#endif