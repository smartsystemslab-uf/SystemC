#include "systemc.h"
#include "gang_ff.cpp"  // Include the module header

SC_MODULE(tb_gang_ffs) {
    sc_signal<sc_uint<WIDTH>> current_state, next_state;
    sc_clock clk{ "clk", 5, SC_NS };  // Clock with a period of 10 ns

    gang_ffs uut{ "Gang_FF" }; // Instantiate the DUT

    void stimulus() {
        // Initialize values
        next_state.write(0);
        wait(5, SC_NS);

        for (int i = 0; i < 10; i++) {
            next_state.write(i);
            wait(5, SC_NS);
      
        }

   
    }

    SC_CTOR(tb_gang_ffs) {
        uut.current_state(current_state);
        uut.clk(clk);
        uut.next_state(next_state);

        SC_THREAD(stimulus); 
        sensitive << clk;
    }
};

// Main function
int sc_main(int argc, char* argv[]) {
    tb_gang_ffs tb("TB_GangFF");
    sc_start(50,SC_NS);
    return 0;
}
