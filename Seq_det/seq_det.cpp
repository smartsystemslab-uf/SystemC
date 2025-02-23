

#include "systemc.h"

SC_MODULE(seq_det) {
    sc_in<bool> clk, data;
    sc_out<bool> seq_found;

    // Using sc_out instead of sc_signal to avoid redefinition issues
    sc_out<bool> first, second, third;

    // Synchronous logic process
    void prc_seq_det() {
        third.write(second.read());
        second.write(first.read());
        first.write(data.read());
    }

    // Combinational logic process
    void prc_output() {
        bool result = first.read() & (!second.read()) & third.read();
        seq_found.write(result);

        std::cout << "Data: " << data.read()
            << " -> Seq Found: " << result
            << " @ " << sc_time_stamp() << std::endl;
    }

    SC_CTOR(seq_det) {
        SC_METHOD(prc_seq_det);
        sensitive << clk.pos();  // Fix: Trigger only on positive clock edge

        SC_METHOD(prc_output);
        sensitive << first << second << third;
    }
};
