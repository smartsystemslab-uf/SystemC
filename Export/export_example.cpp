#include <systemc>
using namespace sc_core;

//defines one module
SC_MODULE(MODULE1) {
    //an export for other modules to connect
    sc_export<sc_signal_in_if<int>> p;
    //a signal (channel) inside the module. If not using export, the channel need to be defined outside module1.
    sc_signal<int> s;
    SC_CTOR(MODULE1) {
        //bind an export to an internal channel
        p(s);
        //a process to write to an internal channel
        SC_THREAD(writer);
    }
    void writer() {
        //init value
        int val = 1;
        while (true) {
            //write to an internal channel
            s.write(val++);
            wait(1, SC_SEC);
        }
    }
};

//a module that reads from an export
SC_MODULE(MODULE2) {
    //a port used to read from an export of another module
    sc_port<sc_signal_in_if<int>> p;
    SC_CTOR(MODULE2) {
        //a process to read from an outside channel
        SC_THREAD(reader);
        //triggered by value change on the channel
        sensitive << p;
        dont_initialize();
    }
    void reader() {
        while (true) {
            //use port to read from the channel, like a pointer.
            std::cout << sc_time_stamp() << ": reads from outside channel, val=" << p->read() << std::endl;
            //receives from port
            wait();
        }
    }
};
