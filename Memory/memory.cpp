#include "systemc.h"

const int WORD_SIZE = 8;
const int ADDR_SIZE = 6;
const int MEM_SIZE = 10; 
SC_MODULE(memory) {
    sc_in<bool> clk, en, rw;
    sc_in<sc_uint<ADDR_SIZE>> addr;
    sc_inout<sc_lv<WORD_SIZE>> data;

    sc_lv<WORD_SIZE> ram[MEM_SIZE];  // Memory storage

    void trans_memory() {
        if (en.read()) {
            if (rw.read()) {  // Read operation
                if (addr.read() < MEM_SIZE) {
                    data.write(ram[addr.read()]);
                    std::cout << "[MEMORY] Read: Addr=" << addr.read()
                        << " Data=" << ram[addr.read()]
                        << " @ " << sc_time_stamp() << std::endl;
                }
                else {
                    std::cout << "[ERROR] Read Out of Range Addr=" << addr.read()
                        << " @ " << sc_time_stamp() << std::endl;
                }
            }
            else {  // Write operation
                if (addr.read() < MEM_SIZE) {
                    ram[addr.read()] = data.read();
                    std::cout << "[MEMORY] Write: Addr=" << addr.read()
                        << " Data=" << data.read()
                        << " @ " << sc_time_stamp() << std::endl;
                }
                else {
                    std::cout << "[ERROR] Write Out of Range Addr=" << addr.read()
                        << " @ " << sc_time_stamp() << std::endl;
                }
            }
        }
    }

    SC_CTOR(memory) {
        SC_METHOD(trans_memory);
        sensitive << clk.pos(); // Update on positive edge of clock
    }
};

