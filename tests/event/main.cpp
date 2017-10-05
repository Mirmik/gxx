#include <iostream>
#include <gxx/event/delegate.h>
#include <gxx/event/multiple_delegate.h>
#include <gxx/event/queue_delegate.h>
#include <gxx/event/once_delegate.h>
#include <gxx/debug/dprint.h>

void hello_world() {
	dprln("HelloWorld");
}

void hello_world1() {
	dprln("HelloWorld1");
}

void hello_world2() {
	dprln("HelloWorld2");
}

int main() {
	//gxx::delegate<void> dlg = hello_world;
	//dlg();
//
	//gxx::multiple_delegate<> mdlg;
//
	//mdlg += hello_world;
	//mdlg += hello_world1;
	//mdlg += hello_world2;
	//mdlg -= hello_world2;
	//mdlg();
//
	//gxx::queue_delegate<> qdlg;
	//qdlg += hello_world;

	gxx::once_delegate<void> odlg = hello_world;
	odlg();
	odlg();

	odlg = hello_world;
	odlg();
	odlg();

}