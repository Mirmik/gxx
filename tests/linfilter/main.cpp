#include <gxx/autocontrol/slinfilter.h>
#include <gxx/container.h>
#include <gxx/print.h>

int main() {

	double input;
	double output;

	gxx::autocontrol::stepped_aperiodic_filter flt(&input, &output);
	flt.set_koeff(1-exp(-1.0/10.0));

	input = 100;
	output = 0;

	for(auto it : gxx::gen::range(0,101)) {
		flt.iteration();
		gxx::fprintln("input: {}, output: {}", input, output);
	}


}