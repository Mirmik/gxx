#include <gxx/trent/gbson.h>

int main() {
    gxx::trent tr;

    tr["a"] = 4;
    tr["b"] = std::string("mir");
    tr["c"][0] = 25;
    tr["c"][1] = std::string("HelloWorld");

    char buf[128];

    int ret = gxx::gbson::dump(tr, buf, 128);
    gxx::println("ret: ", ret);

    if (ret < 0) {
        gxx::println("error in gbson parse");
    }

    gxx::print_dump((const void*)buf, ret);
}
