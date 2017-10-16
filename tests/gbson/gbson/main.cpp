#include <iostream>
#include <gxx/serialize/gbson.h>

#include <string>
#include <gxx/io/bufwriter.h>

int main() {
    char nbuf[128];

    gxx::io::bufwriter writer(nbuf);

    gxx::trent tr(gxx::trent::type::array);
    gxx::trent::array_type& arr = tr.unsafe_array();
    arr.reserve(4);
    arr.push_back(0.785);
    arr.push_back(2.0);
    arr.push_back(3.0);
    arr.push_back(4.0);

    gxx::gbson::print_to(tr, writer);

    //writer.print("HelloWorld");
    //writer.print("HelloWorld");
    //writer.putchar(0);
    debug_print_dump(nbuf, writer.size());

    return 0;
}
