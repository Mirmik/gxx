#ifndef GXX_LAZER_PROXY_H
#define GXX_LAZER_PROXY_H

#include <dataproxy.h>

class LaserProxy {
public:
    std::shared_ptr<std::string> get_data() {
        dprln("get_data");
        return std::make_shared<std::string>("Mirmik");
    }

    std::vector<std::string> types{ "pna", "ena" };

    result<void> set_type(std::string str) {
        if (!gxx::container::contain(types, str)) return error("WrongType");
        return result<void>();
    }

    result<void> bind(std::string str) {
        dprln("bind");
        return error("WrongType");
    }

    result<void> unbind(std::string str) {
        dprln("unbind");
        return error("WrongType");
    }
};

#endif
