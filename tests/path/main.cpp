#include <iostream>
//#include <gxx/path/path.h>
#include <gxx/io/fstream.h>
#include <gxx/argname.h>

using namespace gxx::argument_literal;

int main() {
   // gxx::path::path pth(R"(curdir\mirmik)");

    gxx::io::fstream cout = gxx::io::fstream::from_file_descriptor(1);

    //cout.println(pth);
    //cout.println(pth.is_exist());

    cout.println(67);
    cout.println("MITRMIK");
    cout.println("MITRMIK {}", 68);

    //cout.print("mirmik {}, {}", 90, "lalal"_a=98);
    //printable_format("{} mirmik", 90, "world");
}
