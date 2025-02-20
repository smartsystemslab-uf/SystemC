#include <systemc.h>

// Define FIFO Size


SC_MODULE(Consumer) {
    sc_fifo_in<int> fifo_in; // Input port for FIFO

    void read_process() {
        int data;
        while (true) {
            if (fifo_in.nb_read(data)) // Read from FIFO
                std::cout << "Consumer read: " << data << " at " << sc_time_stamp() << std::endl;
            else
                std::cout << "Consumer read: " << "empty" << " at " << sc_time_stamp() << std::endl;
            wait(1,SC_NS);
        }
    }

    SC_CTOR(Consumer) {
        SC_THREAD(read_process);
    }
};

SC_MODULE(Producer) {
    sc_fifo_out<int> fifo_out; // Output port for FIFO
    sc_in<int> data;
    void write_process() {
        while (true) {
            if (fifo_out.nb_write(data.read())) // Write to FIFO
                std::cout << "Producer wrote: " << data << " at " << sc_time_stamp() << std::endl;
            else
                std::cout << "Producer wrote: " << "full" << " at " << sc_time_stamp() << std::endl;
            wait(1, SC_NS);
        }
    }

    SC_CTOR(Producer) {
        SC_THREAD(write_process);
    }
}; 