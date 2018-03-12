#ifndef GXX_UTIL_TEXT_H
#define GXX_UTIL_TEXT_H

#include <string>

/*def textblock(str):
	return chr(27) + str + chr(27) + "[0m"

def black(str):
	return textblock("[30;1m" + str)

def red(str):
	return textblock("[31;1m" + str)

def green(str):
	return textblock("[32;1m" + str)

def yellow(str):
	return textblock("[33;1m" + str)

def purple(str):
	return textblock("[35;1m" + str)

def cyan(str):
	return textblock("[36;1m" + str)

def white(str):
	return textblock("[37;1m" + str)
*/
namespace gxx {
	namespace text {
		static inline std::string black(const std::string str) {
			return gxx::format("\x1B[30;1m{}\x1B[0m", str);
		}

		static inline std::string red(const std::string str) {
			return gxx::format("\x1B[31;1m{}\x1B[0m", str);
		}

		static inline std::string green(const std::string str) {
			return gxx::format("\x1B[32;1m{}\x1B[0m", str);
		}

		static inline std::string yellow(const std::string str) {
			return gxx::format("\x1B[33;1m{}\x1B[0m", str);
		}

		static inline std::string blue(const std::string str) {
			return gxx::format("\x1B[34;1m{}\x1B[0m", str);
		}

		static inline std::string purple(const std::string str) {
			return gxx::format("\x1B[35;1m{}\x1B[0m", str);
		}

		static inline std::string cyan(const std::string str) {
			return gxx::format("\x1B[36;1m{}\x1B[0m", str);
		}

		static inline std::string white(const std::string str, const char* seq) {
			return gxx::format("\x1B[37;1m{}\x1B[0m", str);
		}
	}
}

#endif