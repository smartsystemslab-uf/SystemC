#include "systemc.h"
#include "fifo.cpp"

#define FIFO_SIZE 4

int sc_main(int argc, char* argv[]) {
    sc_fifo<int> fifo(FIFO_SIZE); // FIFO channel
    sc_signal<int> data;
    Producer producer("Producer");
    Consumer consumer("Consumer");

    producer.fifo_out(fifo); // Connect FIFO output to FIFO channel
    consumer.fifo_in(fifo);  // Connect FIFO input to FIFO channel
    producer.data(data);
    //consumer.data(data);
    sc_trace_file* wf = sc_create_vcd_trace_file("ports_access");
    sc_trace(wf, data, "data");
    sc_start(1, SC_NS);
    data = 5;
    fifo.write(data);
    sc_start(2, SC_NS);
    data = 6;
    fifo.write(data);
    sc_start(2, SC_NS);
    data = 7;
    fifo.write(data);
    sc_start(2, SC_NS);
    data = 8;
    fifo.write(data);
    sc_start(2, SC_NS);
    data = 9;
    fifo.write(data);
    sc_start(2, SC_NS);
    fifo.read();
    sc_start(2, SC_NS);
    fifo.read();
    sc_start(2, SC_NS);
    fifo.read();
    sc_start(2, SC_NS);
    fifo.read();
    sc_start(2, SC_NS);
    fifo.read();
    // Start the testing here
    sc_close_vcd_trace_file(wf);
     // Run simulation for 10 ns
    return 0;
}