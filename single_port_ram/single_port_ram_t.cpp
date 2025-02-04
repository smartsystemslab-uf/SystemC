#include "systemc.h"
#include "single_port_ram.cpp"

int sc_main(int argc, char* argv[]) {
    // Signal Declarations
    sc_signal<sc_uint<3>> address;
    sc_signal<bool> cs;
    sc_signal<bool> we;
    sc_signal<bool> oe;
    sc_signal<sc_uint<4>> data_in;
    sc_signal<sc_uint<4>> data_out;

    // Instantiate Single-Port RAM Module
    ram_sp_ar_aw ram_sp_rw("ram_sp_ar_aw");
    ram_sp_rw.cs(cs);
    ram_sp_rw.we(we);
    ram_sp_rw.oe(oe);
    ram_sp_rw.address(address);
    ram_sp_rw.data_in(data_in);
    ram_sp_rw.data_out(data_out);

    // Create VCD Trace File for Debugging
    sc_trace_file* wf = sc_create_vcd_trace_file("single_port_ram");
    sc_trace(wf, cs, "cs");
    sc_trace(wf, we, "we");
    sc_trace(wf, oe, "oe");
    sc_trace(wf, address, "address");
    sc_trace(wf, data_in, "data_in");
    sc_trace(wf, data_out, "data_out");

    // Initialize Simulation
    sc_start(0, SC_NS);
    std::cout << "Starting RAM Test...\n";

    // **WRITE Operation**
    std::cout << "Writing 6 to address 5...\n";
    cs = true;          // Chip Select Enable
    we = true;          // Write Enable
    oe = false;         // Read Disable
    address = 5;        // Target Address
    data_in = 6;        // Data to Write
    sc_start(10, SC_NS); // **Allow Time for Write Operation**

    // De-assert Write Enable
    we = false;
    sc_start(5, SC_NS);

    // **READ Operation**
    std::cout << "Reading from address 5...\n";
    cs = true;
    oe = true;
    address = 5;
    sc_start(10, SC_NS); // **Allow Time for Read Operation**

    // Print Results
    std::cout << "Expected Data: 6, Actual Data Read: " << data_out.read() << "\n";

    // Close Trace File
    sc_close_vcd_trace_file(wf);
    return 0;
}
