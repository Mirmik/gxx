#include <iostream>
#include <gxx/event/delegate.h>
#include <gxx/event/multiple_delegate.h>
#include <gxx/event/queue_delegate.h>
#include <gxx/event/once_delegate.h>
#include <gxx/debug/dprint.h>

void hello_world() {
	dprln("HelloWorld");
}

int main() {
	gxx::delegate<void> dlg = hello_world;
	dlg();	

	gxx::once_delegate<void> odlg = hello_world;
	odlg();
	//odlg();

	/*odlg = hello_world;
	odlg();
	odlg();*/

}