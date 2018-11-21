#include <gxx/io/fdring.h>
#include <unistd.h>

char arr[128];
gxx::io::fdring_istorage fdring { STDIN_FILENO, arr };

#include <gxx/event/flag.h>

void readfunc(); 
gxx::event::action_flag read_action_flag{readfunc, true};

void readfunc() {
	while(fdring.avail()) dprln((char)fdring.getchar());
	read_action_flag.wait();
};

int main() {
	fdring.set_avail_flag(&read_action_flag);
	
	fdring.start();
	while(1);
}
