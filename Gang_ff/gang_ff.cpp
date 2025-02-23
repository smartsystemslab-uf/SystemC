#include "systemc.h"
const int WIDTH = 4;

SC_MODULE(gang_ffs) {
	sc_out<sc_uint<WIDTH> > current_state;
	sc_in<bool> clk;
	sc_in<sc_uint<WIDTH> > next_state;

	void prc_gang_ffs() { //File: gang_ffs.cpp
		current_state.write(next_state.read());
		std::cout << "CS:" << current_state.read() << " @ " << sc_time_stamp() << endl;
	}

	SC_CTOR(gang_ffs) {
		SC_METHOD(prc_gang_ffs);
		sensitive << clk.pos();
	}
};

