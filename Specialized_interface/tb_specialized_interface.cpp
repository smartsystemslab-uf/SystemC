#include "systemc.h"
#include "specialized_interface.cpp"
SC_MODULE(testbench){
	WRITER w{"w"};
	READER r{"r"};
	sc_signal<bool> b1,b2;
	SC_CTOR(testbench){
	w.p1(b1);
    w.p2(b2);
    r.p1(b1);
    r.p2(b2);
	}
};
int sc_main(int, char*[]) {
 testbench tb("tb");
  sc_start(4, SC_SEC);
  return 0;
}