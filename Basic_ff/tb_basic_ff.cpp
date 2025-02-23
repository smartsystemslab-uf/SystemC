#include "systemc.h"
#include "basic_ff.cpp"

SC_MODULE(testbench) {
    sc_signal<bool> d, q;
    sc_clock clk;

    basic_ff uut;

    void stimulus() {
        d.write(1);
        wait(10, SC_NS);
        d.write(0);
        wait(10, SC_NS);
        d.write(1);
        wait(10, SC_NS);
        d.write(0);
        wait(10, SC_NS);
    }

    SC_CTOR(testbench) : clk("clk", 10, SC_NS), uut("uut") {
        uut.clk(clk);
        uut.d(d);
        uut.q(q);

        SC_THREAD(stimulus);
    }
};

int sc_main(int argc, char* argv[]) {
    testbench tb("tb");
    sc_start(50, SC_NS);
    return 0;
}
