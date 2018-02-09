#include "gxx/diag/diag.h"
#include "gxx/util/stub.h"
#include "assert.h"

struct diag_ops diag_stub = {
	(diag_putc_t) do_nothing,
	(diag_getc_t) do_nothing,
	(diag_write_t) do_nothing,
	(diag_getc_t) do_nothing,
};

struct diag_ops* current_diag = &diag_stub;;

void diag_setup(struct diag_ops* ndiag)
{
	current_diag = ndiag;
};

int diag_putc(char c) {
	return current_diag->putc(c);
};

int diag_getc() {
	return current_diag->getc();
}

int diag_write(const char* buf, int len) {
	return current_diag->write(buf, len);
}

int diag_read(char* buf, int len) {
	return current_diag->read(buf, len);
}

int diag_write_stub(const char* buf, int len) {
	const char *ptr = buf;
	for (;len;len--) diag_putc((int)*ptr++);
}

int diag_read_stub(char* buf, int len) {
	char *ptr = buf;
	for (;len;len--) *ptr++ = diag_getc();
}