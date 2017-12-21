#include <gxx/util/base64.h>
#include <string.h>

#include <gxx/print.h>
#include <gxx/print/stdprint.h>

int main() {
	const char* str = "HelloWorsdfgsdfhgesgjhutrehwouerhgeirjgkidrjhgyairgjasgz;skrohgsutrehgawkejgfn;wa'lhgfa[weirjgawelrjg;oeshgyreg'wjdreg;klawhgeyhgWA'IEGJAWEJGS;KREH;AEPJHGQWREJQAEHGKWAhreg	W4EJNG;AEKRHJ;BSKJTREH;WESJIHWRE[THJERKDSHQPRE5WH[ESJIOld";

	auto res = gxx::base64_encode((const uint8_t*)str, strlen(str));

	gxx::println(str);
	gxx::println(res);
	gxx::println(gxx::base64_decode(res));
}