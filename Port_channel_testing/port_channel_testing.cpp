#include <systemc>
using namespace sc_core;
//defines one module
SC_MODULE(MODULE1) {
//a signal (channel) inside the module
  sc_signal<int> s;
//a port used to write to an outside channel
  sc_port<sc_signal_out_if<int> > p;
  SC_CTOR(MODULE1) {
//a process to write to own channel
    SC_THREAD(selfWrite);
//a process to read from own channel
    SC_THREAD(selfRead);
// triggered by value change on the channel
    sensitive << s;
    dont_initialize();
//a process to write to an outside channel
    SC_THREAD(outsideWrite);
  }
  void selfWrite() {
//init value
    int val = 1;
    while (true) {
//write to own channel
      s.write(val++);
//repeat after 1 s
      wait(1, SC_SEC);
    }
  }
  void selfRead() {
    while (true) {
//read from own channel
      std::cout << sc_time_stamp() << ": reads from own channel, val=" << s.read() << std::endl;
//receives from signal
      wait();
    }
  }
  void outsideWrite() {
//init value
    int val = 1;
    while (true) {
//write to an outside channel, calls the write method of the outside channel. p is a pointer.
      p->write(val++);
      wait(1, SC_SEC);
    }
  }
};

//a module that reads from an outside channel
SC_MODULE(MODULE2) {
//a port used to read from an outside channel
  sc_port<sc_signal_in_if<int> > p;
  SC_CTOR(MODULE2) {
//a process to read from an outside channel
    SC_THREAD(outsideRead);
//triggered by value change on the channel
    sensitive << p;
    dont_initialize();
  }
  void outsideRead() {
    while (true) {
//use port to read from the channel, like a pointer.
      std::cout << sc_time_stamp() << ": reads from outside channel, val=" << p->read() << std::endl;
// receives from port
      wait();
    }
  }
};
