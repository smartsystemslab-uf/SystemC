#include <systemc>
using namespace sc_core;

//a submodule that writes to channel
SC_MODULE(SUBMODULE1) {
    sc_port<sc_signal_out_if<int>> p;
    SC_CTOR(SUBMODULE1) {
        SC_THREAD(writer);
    }
    void writer() {
        //init value
        int val = 1;
        while (true) {
            //write to channel through port
            p->write(val++);
            wait(1, SC_SEC);
        }
    }
};

//a submodule that reads from channel
SC_MODULE(SUBMODULE2) {
    sc_port<sc_signal_in_if<int>> p;
    SC_CTOR(SUBMODULE2) {
        SC_THREAD(reader);
        //triggered by value change on the channel
        sensitive << p;
        dont_initialize();
    }
    void reader() {
        while (true) {
            std::cout << sc_time_stamp() << ": reads from channel, val=" << p->read() << std::endl;
            //receives from channel through port
            wait();
        }
    }
};

//top-level module
SC_MODULE(MODULE1) {
    
        sc_port<sc_signal_out_if<int>> p;
    //declares submodule
    SUBMODULE1 sub1;
    //instantiate submodule
    SC_CTOR(MODULE1) : sub1("sub1") {
        //bind submodule's port directly to parent's port
        sub1.p(p);
    }
};

SC_MODULE(MODULE2) {
    sc_port<sc_signal_in_if<int>> p;
    SUBMODULE2 sub2;
    SC_CTOR(MODULE2) : sub2("sub2") {
        //bind submodule's port directly to parent's port
        sub2.p(p);
    }
};
