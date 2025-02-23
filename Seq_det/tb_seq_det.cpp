#include "systemc.h"
#include "seq_det.cpp"  // Include the header file

SC_MODULE(tb_seq_det) {
    sc_signal<bool> data, seq_found,first,second,third;
    sc_clock clk{ "clk", 5, SC_NS };  // 10 ns clock period

    seq_det uut{ "Seq_Det" };

    void stimulus() {
        // Initialize values
        data.write(0);
        wait(1, SC_NS);

        // Apply a sequence of inputs
        bool input_sequence[] = { 0, 1, 0, 1, 1, 0, 1, 0 };
        for (int i = 0; i < 8; i++) {
            data.write(input_sequence[i]);
            wait(5, SC_NS);
        }

        
    }

    SC_CTOR(tb_seq_det) {
        uut.clk(clk);
        uut.data(data);
        uut.seq_found(seq_found);
        uut.first(first);
        uut.second(second);
        uut.third(third);


        SC_THREAD(stimulus);
        sensitive << clk;
    }
};

// Main function
int sc_main(int argc, char* argv[]) {
    tb_seq_det tb("TB_Seq_Det");
    sc_start(100,SC_NS);
    return 0;
}
