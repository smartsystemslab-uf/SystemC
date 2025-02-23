#include "systemc.h"

SC_MODULE(basic_ff){
  sc_in<bool> clk, d;  
  sc_out<bool> q;

void prc_basic_ff(){
q.read(d.write());
std::cout << "q:" << q << " @ " << sc_time_stamp() <<endl;
}

  SC_CTOR(basic_ff) {
    SC_METHOD(prc_basic_ff);
    sensitive_pos << clk.pos();
};

