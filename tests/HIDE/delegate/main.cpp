#include <gxx/delegate.h>
#include <gxx/debug/dprint.h>

void func(int i) {
	dpr("func");
	dprln(i);
}

int main() {
	gxx::delegate<void,int> dlg;
	dlg(32);

	dlg = func;
	dlg(48);

}