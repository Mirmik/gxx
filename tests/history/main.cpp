#include <iostream>
#include <gxx/history.h>

int main() {
	gxx::history hist(6);

	hist.push_string("Hello1");
	hist.push_string("Hello2");
	hist.push_string("Hello3");
	hist.push_string("Hello4");
	hist.push_string("Hello5");
	hist.push_string("Hello6");
	hist.push_string("Hello7");
	hist.push_string("Hello8");
	
	dprln(hist[-1]);
	dprln(hist[-2]);
	dprln(hist[-3]);
	dprln(hist[-4]);
	dprln(hist[-5]);
	dprln(hist[-6]);
}