#include <gxx/util/base64.h>
#include <string.h>

#include <gxx/print.h>
#include <gxx/print/stdprint.h>

int main() {
	/*const char* str = "HelloWorsdfgsdfhgesgjhutrehwouerhgeirjgkidrjhgyairgjasgz;skrohgsutrehgawkejgfn;wa'lhgfa[weirjgawelrjg;oeshgyreg'wjdreg;klawhgeyhgWA'IEGJAWEJGS;KREH;AEPJHGQWREJQAEHGKWAhreg	W4EJNG;AEKRHJ;BSKJTREH;WESJIHWRE[THJERKDSHQPRE5WH[ESJIOld";

	auto res = gxx::base64_encode((const uint8_t*)str, strlen(str));

	gxx::println("str:");
	gxx::println(str);
	gxx::println("res:");
	gxx::println(res);

	gxx::println("dec:");*/

	std::string str("saturn852");

	auto g = std::hash<std::string>()(str);
	dprhex(g);

	auto res0 = gxx::base64_decode("p3luH+iSL5SOxekYINONPw==");
	auto res1 = gxx::base64_decode("q6UtAq0EnYJjihKbI4iLcw==");






	gxx::print_dump(res0.data(), res0.size());
	gxx::println();
	gxx::print_dump(res1.data(), res1.size());

	gxx::println(*(int64_t*)(res0.data()));
	gxx::println(*(int32_t*)(res0.data()));
	gxx::println(*(int64_t*)(res1.data()));
	gxx::println(*(int32_t*)(res1.data()));
}