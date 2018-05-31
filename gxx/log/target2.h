#ifndef GXX_LOG_TARGET_H
#define GXX_LOG_TARGET_H

using namespace gxx::argument_literal;

namespace gxx {
	namespace log {
		struct target {
			virtual void log(std::shared_ptr<logmessage> logmsg) {
				gxx::println("virtual log function");
			}
		};

		struct stdout_target : public target {
			std::string tmplt = "| {msg} |";

			void log(std::shared_ptr<logmessage> logmsg) override {
				gxx::fprintln(tmplt.c_str(), "msg"_a=logmsg->message);
			}
		};
	}
}

#endif
