#include "systemc.h"
#include "fsm_moore2.cpp"

SC_MODULE(tb_fsm_moore) {
    sc_signal<bool> a, reset, output;
    sc_clock clk{ "clk", 2, SC_NS }; // 10ns clock period

    moore2 fsm { "FSM" };

    void stimulus() {
        std::cout << "\n===== Starting Moore FSM Test =====\n";

        // Apply reset
        reset.write(1);
        a.write(0);
        wait(2, SC_NS);

        // Release reset
        reset.write(0);

        bool input_sequence[] = { 1, 0, 1, 1, 0, 1, 0 };
        for (int i = 0; i < 7; i++) {
            a.write(input_sequence[i]);
            wait(2, SC_NS);
        }

        std::cout << "===== Simulation Completed =====\n";
        
    }

    SC_CTOR(tb_fsm_moore) {
        fsm.clk(clk);
        fsm.a(a);
        fsm.reset(reset);
        fsm.output(output);

        SC_THREAD(stimulus);
        sensitive << clk;
    }
};

// Main function
int sc_main(int argc, char* argv[]) {
    tb_fsm_moore tb("TB_FSM");
    sc_start(50, SC_NS);
    return 0;
}
