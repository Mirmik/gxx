#include "gxx/diag/diag.h"
#include "gxx/util/stub.h"

struct diag_ops diag_stub = {
	(diag_putc_t) do_nothing,
	(diag_getc_t) do_nothing,
	(diag_write_t) do_nothing,
	(diag_getc_t) do_nothing,
};

struct diag_ops* current_diag_ops = &diag_stub;
void* current_diag_priv = NULL;

void diag_setup(struct diag_ops* ndiag, void* priv) {
	current_diag_ops = ndiag;
	current_diag_priv = priv;
};

int diag_putc(void* priv, char c) {
	return current_diag_ops->putc(current_diag_priv, c);
};

int diag_getc() {
	return current_diag_ops->getc(current_diag_priv);
}

int diag_write(const char* buf, int len) {
	return current_diag_ops->write(current_diag_priv, buf, len);
}

int diag_read(char* buf, int len) {
	return current_diag_ops->read(current_diag_priv, buf, len);
}

int diag_write_stub(void*, const char* buf, int len) {
	const char *ptr = buf;
	for (;len;len--) diag_putc((int)*ptr++);
}

int diag_read_stub(void*, char* buf, int len) {
	char *ptr = buf;
	for (;len;len--) *ptr++ = diag_getc();
}