#include "systemc.h"
#define DATA_WIDTH        4
#define ADDR_WIDTH        3 
#define RAM_DEPTH        1 << ADDR_WIDTH
SC_MODULE(ram_sp_ar_aw) {
    sc_in    <sc_uint<ADDR_WIDTH> > address;
    sc_in    <bool>                 cs;
    sc_in    <bool>                 we;
    sc_in    <bool>                 oe;
    sc_in    <sc_uint<DATA_WIDTH> > data_in;
    sc_out   <sc_uint<DATA_WIDTH> > data_out;
    sc_uint <DATA_WIDTH> mem[RAM_DEPTH];

    // Memory Write Block 
    // Write Operation : When we = 1, cs = 1
    void write_mem() {
        if (cs.read() && we.read()) {
            mem[address.read()] = data_in.read();
        }
    }
    // Memory Read Block 
    // Read Operation : When we = 0, oe = 1, cs = 1
    void read_mem() {
        if (cs.read() && !we.read() && oe.read()) {
            data_out.write(mem[address.read()]);
        }
        cout << "@" << sc_time_stamp() << " data_out:" << data_out << endl;
    }
    SC_CTOR(ram_sp_ar_aw) {
        SC_METHOD(read_mem);
        sensitive << address << cs << we << oe;
        SC_METHOD(write_mem);
        sensitive << address << cs << we << data_in;
    }

};
