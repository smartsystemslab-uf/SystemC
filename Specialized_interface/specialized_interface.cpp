#include <systemc>
using namespace sc_core;

SC_MODULE(WRITER) {
//specialized ports
  sc_out<bool> p1, p2;
  SC_CTOR(WRITER) {
    SC_THREAD(writer);
//#10, initialize default value to true
    p1.initialize(true);
  }
  void writer() {
    bool v = true;
    while (true) {
//#2 write through port
      p1->write(v);
//value change
      v = !v;
//repeat after 1 s
      wait(1, SC_SEC);
    }
  }
};

SC_MODULE(READER) {
//specialized ports
  sc_in<bool> p1, p2;
  SC_CTOR(READER) {
    SC_THREAD(reader1);
//#3 default_event(), same as p->default_event() or p.default_event()
    sensitive << p1 << p2;
    dont_initialize();
    SC_THREAD(reader2);
//#11, sensitive to value change event of an un-bound port
    sensitive << p1.value_changed();
    dont_initialize();
    SC_THREAD(reader3);
//#13, sensitive to neg event of an un-bound port
    sensitive << p1.neg();
    dont_initialize();
    SC_THREAD(reader4);
//#12, sensitive to pos event of an un-bound port
    sensitive << p1.pos();
    dont_initialize();
  }
  void reader1() {
    while (true) {
//#1 read(), #4 event()
      std::cout << sc_time_stamp() << ": default_event. p1 = " << p1->read() << "; p1 triggered? " << p1->event() << "; p2 triggered? " << p2->event() << std::endl;
      wait();
    }
  }
  void reader2() {
    while (true) {
//#1 read()
      std::cout << sc_time_stamp() << ": value_changed_event. p1 = " << p1->read() <<  std::endl;
      wait();
    }
  }
  void reader3() {
    while (true) {
//#8, if negedge happened
      std::cout << sc_time_stamp() << ": negedge_event. p1 = " << p1->read() << "; negedge = " << p1->negedge() << std::endl;
      wait();
    }
  }
  void reader4() {
    while (true) {
//#6, if posedge happened
      std::cout << sc_time_stamp() << ": posedge_event. p1 = " << p1->read() <<  "; posedge = " << p1->posedge() << std::endl;
      wait();
    }
  }
};


int sc_main(int, char*[]) {
//instantiate writer
  WRITER writer("writer");
//instantiate reader
  READER reader("reader");
declare boolean signal channel
  sc_signal<bool> b1, b2;
//port binding
  writer.p1(b1);
  writer.p2(b2);
  reader.p1(b1);
  reader.p2(b2);
  sc_start(4, SC_SEC);
  return 0;
}

Result:
false to true
0 s: posedge_event. p1 = 1; posedge = 1
false to true
0 s: value_changed_event. p1 = 1
false to true; p2 never triggered
0 s: default_event. p1 = 1; p1 triggered? 1; p2 triggered? 0
true to false
1 s: negedge_event. p1 = 0; negedge = 1
true to false
1 s: value_changed_event. p1 = 0
true to false
1 s: default_event. p1 = 0; p1 triggered? 1; p2 triggered? 0
false to true
2 s: posedge_event. p1 = 1; posedge = 1
false to true
2 s: value_changed_event. p1 = 1
false to true
2 s: default_event. p1 = 1; p1 triggered? 1; p2 triggered? 0
true to false
3 s: negedge_event. p1 = 0; negedge = 1
true to false
3 s: value_changed_event. p1 = 0
true to false
3 s: default_event. p1 = 0; p1 triggered? 1; p2 triggered? 0
