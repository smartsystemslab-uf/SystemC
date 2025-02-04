#include "systemc.h"
#include "counter.cpp"

int sc_main(int argv, char* agrv[])
{
    sc_signal<sc_uint<4>> a, b, sum;
    adder add("adder");
    add.a(a);
    add.b(b);
    add.sum(sum);
    sc_start(0, SC_NS);
    // Open VCD file
    sc_trace_file* wf = sc_create_vcd_trace_file("ports_access");
    sc_trace(wf, a, "a");
    sc_trace(wf, b, "b");
    sc_trace(wf, sum, "sum");
    // Start the testing here
    sc_start(1, SC_NS);
    a = '5';
    b = '5';
    sc_start(1, SC_NS);
    a = '0';
    sc_start(1, SC_NS);
    b = '5';
    sc_start(2, SC_NS);

    sc_close_vcd_trace_file(wf);
    return 0;// Terminate simulation
}