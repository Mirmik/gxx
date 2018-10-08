#include <gxx/debug/dprint.h>
#include <stdio.h>

#include <gxx/datastruct/sline.h>

struct sline sl;
char buf[128];

int main() 
{
	sline_init(&sl, buf, 128);
	sline_write(&sl, "HelloWorld", 10);

	debug_write(sl.buf, sl.len);
	printf("%*s\n", sl.len, sl.buf);
}