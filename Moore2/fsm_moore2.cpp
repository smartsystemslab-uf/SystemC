

#include "systemc.h"

SC_MODULE(moore2) {
    sc_in<bool> clk, a, reset;
    sc_out<bool> output;
    // Define FSM states
    enum state_type { s0, s1, s2, s3 };
    sc_signal<state_type> current_state, next_state;

    // State transition function
    void moore_trans() {
        if (reset.read()) {
            current_state.write(s0);
        }
        else {
            switch (current_state.read()) {
            case s0: next_state.write(a.read() ? s0 : s2); break;
            case s1: next_state.write(a.read() ? s0 : s2); break;
            case s2: next_state.write(a.read() ? s2 : s3); break;
            case s3: next_state.write(a.read() ? s1 : s3); break;
            }
        }
        current_state.write(next_state.read()); // Update state
        // Print debug information
        std::cout << "Time: " << sc_time_stamp() << " | Reset: " << reset.read()  << " | Input A: " << a.read() << " | Current State: " << current_state.read()
            << " | Next State: " << next_state.read() << " | Output: " << output.read()<< std::endl;
    }

    // Moore output logic
    void moore_output() {
        switch (current_state.read()) {
        case s0:
        case s1:
            output.write(1);
            break;
        case s2:
        case s3:
            output.write(0);
            break;
        }
    }

    SC_CTOR(moore2) {
        SC_METHOD(moore_trans);
        sensitive << clk.pos();

        SC_METHOD(moore_output);
        sensitive << current_state;
    }
};


