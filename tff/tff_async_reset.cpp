#include "systemc.h"

SC_MODULE(tff_async_reset) {
    sc_in    <bool> data, clk, reset;
    sc_out   <bool> q;

    bool q_l=0;

    void tff() {
        if (reset.read() == true) {
            q_l = 0;
        }
        else if (reset.read() == false and data.read()==true) {
            q_l = !q_l;
        }
        q.write(q_l);
        cout << "@" << sc_time_stamp() << " q:" << q << endl;
       
    }
   

    SC_CTOR(tff_async_reset) {
        SC_METHOD(tff);
        sensitive << reset;
        sensitive << clk.pos();
    }

};
