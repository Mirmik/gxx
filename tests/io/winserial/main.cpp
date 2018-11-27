#include <iostream>
#include <gxx/io/serial_port.h>

using namespace std;




int main()
{
    const char* cmd = "\0014000000000E4\003";

    char readbuf[20];

    gxx::io::serial_port_file port("COM4", 115200, gxx::serial::parity_even);

    int ret = port.write(cmd, strlen(cmd));
    gxx::println("write", ret);

    ret = port.read(readbuf, 20);
    gxx::println("read", ret);

    gxx::print_dump(readbuf, 20);

    return 0;
}
