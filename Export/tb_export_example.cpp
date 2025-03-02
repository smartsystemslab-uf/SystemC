#include "systemc.h"
#include "export_example.cpp"
SC_MODULE(testbench) {

	MODULE1 m1{ "m1" };
	MODULE2 m2{ "m2" };
	SC_CTOR(testbench) {
		m2.p.bind(m1.p);
	}

};
int sc_main(int, char* []) {
	testbench tb("tb");
	sc_start(10, SC_SEC);
	return 0;
}
