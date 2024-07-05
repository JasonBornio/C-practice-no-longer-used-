#include "mux.h"

class Control {
    public:
        Control();

        void clock_step(bool inputs[][32], int num_inputs, bool control_signal[2]);
        void get_output(bool array[32]);

        void print();

    private:



        bool alu_control[4] = {false, false, false, false};

        bool alu_src;
        bool reg_dst;
        bool reg_wrt;
        bool mem_read;
        bool mem_wrt;
        bool mem_to_reg;
        bool branch;

        bool jump;


};

Control::Control(){
    alu_src = false;
    reg_dst = false;
    reg_wrt = false;
    mem_read = false;
    mem_wrt = false;
    mem_to_reg = false;
    branch = false;

    jump = false;
}

