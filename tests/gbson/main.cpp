#include <iostream>
#include <gxx/serialize/gbson.h>
#include <gxx/serialize/json.h>

#include <string>
#include <gxx/io/bufwriter.h>
#include <gxx/io/bufreader.h>

#include <gxx/gstuff/sender.h>
#include <gxx/debug/debug_ostream.h>

int main() {
    char nbuf[128];

    gxx::io::bufwriter writer(nbuf);

    gxx::trent tr(gxx::trent::type::array);
    gxx::trent::array_type& arr = tr.unsafe_array();
    arr.reserve(4);
    arr.push_back(22);
    //arr.push_back((float)2.0);
    arr.push_back(280);
    arr.push_back(4);

    gxx::gbson::dump(tr, writer);

    //writer.print("HelloWorld");
    //writer.print("HelloWorld");
    //writer.putchar(0);
    debug_print_dump(nbuf, writer.size());

    auto res = gxx::gbson::parse(gxx::io::bufreader(nbuf));

//dprln(res.unwrap()[0].as_integer());
    gxx::json::pretty_print_to(res, std::cout);

    dprln();

    gxx::debug_ostream dout;
    dout.hexmode(true);
    gxx::gstuff::sender messenger(dout);

    messenger.start_message();
    messenger.println("HelloWorld");
    messenger.end_message();

    dprln();

    return 0;
}
