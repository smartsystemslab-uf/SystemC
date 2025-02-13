#include <systemc.h>

SC_MODULE(sc_semaphore_example) {
    sc_in<bool> clock;
    sc_semaphore bus;
    int cnt;

    void bus_semaphore() {
        while (true) {
            wait();
            cout << "@" << sc_time_stamp() << " Check if semaphore is 0 " << endl;
            if (bus.get_value() == 0) {
                cout << "@" << sc_time_stamp() << " Posting 2 to semaphore " << endl;
                bus.post();
                bus.post();
                if (cnt >= 3) {
                    sc_stop(); // Stops the simulation
                }
                cnt++;
            }
        }
    }

    void do_read() {
        while (true) {
            wait();
            cout << "@" << sc_time_stamp() << " Checking semaphore for instance 0" << endl;
            // Check if semaphore is available
            if (bus.trywait() != -1) {
                cout << "@" << sc_time_stamp() << " Got semaphore for instance 0" << endl;
                wait(2, SC_NS);
            }
        }
    }

    void do_write() {
        while (true) {
            wait();
            cout << "@" << sc_time_stamp() << " Checking semaphore for instance 1" << endl;
            // Wait till semaphore is available
            bus.wait();
            cout << "@" << sc_time_stamp() << " Got semaphore for instance 1" << endl;
            wait(3, SC_NS);
        }
    }

    SC_CTOR(sc_semaphore_example) : bus(0) {
        cnt = 0;
        SC_CTHREAD(do_read, clock.pos());
        SC_CTHREAD(do_write, clock.pos());
        SC_CTHREAD(bus_semaphore, clock.pos());
    }
};

int sc_main(int argc, char* argv[]) {
    sc_clock clock("my_clock", 1, SC_NS, 0.5); // Correct clock instantiation

    sc_semaphore_example object("semaphore");
    object.clock(clock);  // Corrected connection

    sc_start(50, SC_NS); // Run simulation for 50 ns

    return 0; // Terminate simulation
}
