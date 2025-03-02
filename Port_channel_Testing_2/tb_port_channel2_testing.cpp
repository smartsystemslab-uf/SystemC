#include "systemc.h"
#include "port_channel2_testing.cpp"
SC_MODULE(testbench)
{
	MODULE1 m1{ "m1" };
	MODULE2 m2{ "m2" };
	sc_signal<int>s;

	SC_CTOR(testbench) {
		m1.p(s);
		m2.p(s);
	}
};
int sc_main(int, char* []) {
	testbench tb("tb");
	sc_start(10, SC_SEC);
	return 0;
}
