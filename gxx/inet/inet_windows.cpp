#include <gxx/inet/hostaddr.h>
#include <winsock2.h>

gxx::inet::netaddr::netaddr(unsigned long addr, unsigned short port) : addr(ntohl(addr)), port(ntohs(port)) {}
