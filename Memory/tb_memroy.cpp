#include "systemc.h"
#include "memory.cpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 10, SC_NS);  // 10ns clock period
    sc_signal<bool> en, rw;
    sc_signal<sc_uint<ADDR_SIZE>> addr;
    sc_signal<sc_lv<WORD_SIZE>> data;

    memory my_ram("my_ram");

    my_ram.clk(clk);
    my_ram.en(en);
    my_ram.rw(rw);
    my_ram.addr(addr);
    my_ram.data(data);

    std::cout << "\n===== Starting Memory Simulation =====" << std::endl;

    // **WRITE to Memory**
    for (int i = 0; i < MEM_SIZE; i++) {
        en.write(1);
        rw.write(0);  // Write mode
        addr.write(i);
        data.write(i * 10); // Example values: 0, 10, 20, ...
        sc_start(10, SC_NS); // Sync with clock
    }

    std::cout << "\n===== Reading from Memory =====" << std::endl;

    // **READ from Memory**
    for (int i = 0; i < MEM_SIZE; i++) {
        en.write(1);
        rw.write(1);  // Read mode
        addr.write(i);
        sc_start(10, SC_NS); // Sync with clock

        std::cout << "[TESTBENCH] Read Addr=" << i
            << " -> Data=" << data.read()
            << " @ " << sc_time_stamp() << std::endl;
    }

    std::cout << "\n===== Simulation Completed =====" << std::endl;
    return 0;
}
