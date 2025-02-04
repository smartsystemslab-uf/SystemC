#include "systemc.h"
#include "counter.cpp"
int sc_main(int argc, char* argv[]) {
    sc_signal<bool> data, clk, reset, q;
    tff_async_reset tar("tff_async_reset");
    tar.data(data);
    tar.reset(reset);
    tar.clk(clk);
    tar.q(q);
    sc_start(1, SC_NS);
    sc_trace_file* wf = sc_create_vcd_trace_file("counter");
    // Dump the desired signals
    sc_trace(wf, clk, "clk");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, data, "data");
    sc_trace(wf, q, "q");
    sc_start(2, SC_NS);
    for (int i = 0;i < 5;i++) {
        clk = sc_bit("0");
        sc_start(1, SC_NS);
        clk = sc_bit("1");
        sc_start(1, SC_NS);
    }
    // Assert reset
    reset = sc_bit('1');
    cout << "@" << sc_time_stamp() << " Asserting reset" << endl;
    // Deassert reset
    sc_start(1, SC_NS);
    reset = sc_bit('0');
    cout << "@" << sc_time_stamp() << " De-Asserting reset" << endl;
    // Assert data
    sc_start(1, SC_NS);
    data = sc_bit('1');
    sc_start(1, SC_NS);
    data = sc_bit('0');
    sc_start(2, SC_NS);
    data = sc_bit('1');
    sc_start(2, SC_NS);

    sc_close_vcd_trace_file(wf);
    return 0;
}
