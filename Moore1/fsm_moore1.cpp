#include "systemc.h"

SC_MODULE(fsm_moore) {
    sc_in<bool> clk, a, reset;
    sc_out<bool> output;

    // Define FSM states
    enum state_type { s0, s1, s2, s3 };
    sc_signal<state_type> current_state, next_state;

    void moore_trans() {
        if (reset.read()) {
            current_state.write(s0);
            output.write(0);
        }
        else {
            switch (current_state.read()) {
            case s0: output.write(1); next_state.write(a.read() ? s0 : s2); break;
            case s1: output.write(0); next_state.write(a.read() ? s1 : s2); break;
            case s2: output.write(1); next_state.write(a.read() ? s2 : s3); break;
            case s3: output.write(1); next_state.write(a.read() ? s1 : s3); break;
            }
        }

        // Move state update outside switch to ensure it happens every clock cycle
        current_state.write(next_state.read());

        // Print debug information
        std::cout << "Time: " << sc_time_stamp()
            << " | Reset: " << reset.read()
            << " | Input A: " << a.read()
            << " | Current State: " << current_state.read()
            << " | Next State: " << next_state.read()
            << " | Output: " << output.read()
            << std::endl;
    }

    SC_CTOR(fsm_moore) {
        SC_METHOD(moore_trans);
        sensitive << clk.pos() ;
    }
};

