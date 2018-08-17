#ifndef GXX_SIMPLE_SHELL_H
#define GXX_SIMPLE_SHELL_H

#include <gxx/datastruct/argvc.h>

#define SSHELL_ARGCMAX 10

#define SSHELL_OK 0
#define SSHELL_EMPTY_STRING -1
#define SSHELL_FUNCTION_NOT_EXIST -2

struct sshell_command {
	const char* name;
	int (*func) (int, char**);
};

int sshell_execute(char* str, const sshell_command* cmd, int cmdlen, int* retptr) {
	char* argv[SSHELL_ARGCMAX];
	int argc;
	int res;

	if (*str == '\0') {
		return SSHELL_EMPTY_STRING;
	}

	argc = argvc_internal_split(str, argv, SSHELL_ARGCMAX);

	for(int i = 0; i < cmdlen; ++i) {
		if (!strcmp(argv[0], cmd[i].name)) {
			res = cmd[i].func(argc, argv);
			if (retptr) *retptr = res;
			return SSHELL_OK;
		}
	}

	return SSHELL_FUNCTION_NOT_EXIST;
}

int sshell_execute_safe(const char* str, const sshell_command* cmd, int cmdlen, int* retptr) {
	char locstr[strlen(str) + 1];
	strcpy(locstr, str);
	return sshell_execute(locstr, cmd, cmdlen, retptr);
}



#ifdef __cplusplus
#include <gxx/event/delegate.h>

namespace gxx{
	struct [[deprecated]] sshell {
		struct command {
			const char* name;
			int (*func) (int, const char**);
		};

		command* table;
		size_t table_size;

		void settable(command* tbl, size_t size) {
			table = tbl;
			table_size = size;
		}
		static constexpr uint8_t OK = 0;
		static constexpr uint8_t FunctionNotExist = -1;
		static constexpr uint8_t EmptyString = -2;

		int __execute_nosafe(char* str, int* ret) {
			str_argvc_t str_argvc(str);

			auto argc = str_argvc.argc();
			auto argv = str_argvc.argv();

			if (strlen(str) == 0)  {
				return EmptyString;
			}

			for(int i = 0; i < table_size; ++i) {
				if (!strcmp(argv[0], table[i].name)) {
					int res = table[i].func(argc, argv);
					if (ret) *ret = res;
					return OK;
				}
			}

			return FunctionNotExist;
		}

		int execute(const char* _str, int* ret = nullptr) {
			char str[128];
			strcpy(str,_str);
			return __execute_nosafe(str, ret);
		}

		int execute(const char* _str, int len, int* ret = nullptr) {
			char str[128];
			memcpy(str,_str,len);
			str[len] = 0;
			return __execute_nosafe(str, ret);
		}
	};
}
#endif

#endif
