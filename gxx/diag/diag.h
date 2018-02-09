#ifndef GENOS_DIAG_H
#define GENOS_DIAG_H

//Diag является отладочным интерфейсом ввода-вывода для таких систем, как debug_print, printk.
//Указанные системы используют функции, смонтированные в cdiag (current diag)
//Diag не регламинтирует, используется ли он для вывода в виде потока байт, 
//консольного форматированного вывода,
//или вывода в файл. То есть cdiag является просто точкой монтирования функций ввода-вывода,
//используемых отладочным вводом-выводом.

#include <sys/cdefs.h>

__BEGIN_DECLS

struct diag_ops 
{
	int (*putc)(char c);
	int (*getc)();
	int (*write)(const char* buf, int n);
	int (*read)(char* buf, int n);
};

typedef int(*diag_putc_t)(char);
typedef int(*diag_getc_t)();
typedef int(*diag_write_t)(const char*, int);
typedef int(*diag_read_t)(char*, int);;

extern struct diag_ops* current_diag;

void diag_setup(struct diag_ops* ndiag);
int diag_putc(char c);
int diag_getc();
int diag_write(const char* buf, int len);
int diag_read(char* buf, int len);

int diag_write_stub(const char* buf, int len);
int diag_read_stub(char* buf, int len);

__END_DECLS

#endif