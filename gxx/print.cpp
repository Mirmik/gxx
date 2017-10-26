#include <gxx/print.h>
#include <gxx/buffer.h>
#include <gxx/io/ostream.h>

namespace gxx {
	
	/*int print_functions<int>::print(gxx::io::ostream& o, const int& i) { 
		char buf[48]; 
		i64toa(i, buf, 10); 
		return o.print(buf); 
	}	

	template<> int print_functions<long>::print(gxx::io::ostream& o, const long& i) { 
		char buf[48]; 
		i64toa(i, buf, 10); 
		return o.print(buf); 
	}


	template<> int print_functions<long long>::print(gxx::io::ostream& o, const long long& i) { 
		char buf[48]; 
		i64toa(i, buf, 10); 
		return o.print(buf); 
	}

	template<> int print_functions<unsigned int>::print(gxx::io::ostream& o, const unsigned int& i) { 
		char buf[48]; 
		i64toa(i, buf, 10); 
		return o.print(buf); 
	}	

	template<> int print_functions<unsigned long>::print(gxx::io::ostream& o, const unsigned long& i) { 
		char buf[48]; 
		i64toa(i, buf, 10); 
		return o.print(buf); 
	}


	template<> int print_functions<unsigned long long>::print(gxx::io::ostream& o, const unsigned long long& i) { 
		char buf[48]; 
		i64toa(i, buf, 10); 
		return o.print(buf); 
	}

	int print_functions<char*>::print(gxx::io::ostream& o, const char* const& i) { 
		return o.print(i); 
	}*/
}