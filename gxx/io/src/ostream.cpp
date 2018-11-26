#include <gxx/io/ostream.h>
#include <gxx/io/spec.h>

#include <gxx/panic.h>

ssize_t gxx::io::ostream::format_print(int32_t num, gxx::buffer opts) 
{
	gxx::io::integer_spec spec(opts);
	return format_print(num, spec);	
}

ssize_t gxx::io::ostream::format_print(int32_t num, const gxx::io::integer_spec& spec) 
{
	char body[32];

	if (spec.width > 32) panic("fprint");
	i32toa(num, body, 10);

	return format_print(body, strlen(body), spec);
}

ssize_t gxx::io::ostream::format_print(const char* str, gxx::buffer opts) 
{
	gxx::io::text_spec spec(opts);
	return format_print(str, strlen(str), spec);	
}

ssize_t gxx::io::ostream::format_print(const char* body, size_t bodylen, const gxx::io::basic_spec& spec) 
{
	int ret = 0;
	if (spec.width > 32) panic("fprint");

	char prefix_symb = ' ';
	int prefix_len = 0;

	char postfix_symb = ' ';
	char postfix_len = 0;

	int difflen = spec.width - bodylen;
	if (difflen > 0) 
	{
		switch (spec.align) {
			case alignment::left:
				postfix_len = difflen;
				break;

			case alignment::right:
				prefix_len = difflen;
				break;

			case alignment::center:
				prefix_len = difflen / 2;
				postfix_len = difflen / 2;
				if (difflen % 2) prefix_len++; 
				break;
		}
	}

	if (prefix_len) {
		ret += fill(prefix_symb, prefix_len);
	}

	ret += write(body, bodylen);

	if (postfix_len) {
		ret += fill(postfix_symb, postfix_len);		
	}

	return ret;
}