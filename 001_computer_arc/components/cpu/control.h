#include "mux.h"

class Control {
    public:
        Control();

        void clock_step(bool inputs[][32], int num_inputs, bool control_signal[2]);
        void get_output(bool array[14]);
        void set_signals(bool arr[12]);

        void print();

        bool alu_control[6] = {false, false, false, false, false, false};

        bool alu_src;
        bool reg_dst;
        bool reg_wrt;
        bool mem_read;
        bool mem_wrt;
        bool mem_to_reg;
        bool branch;

        bool jump;

    private:
        bool signals[14] = {};

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

void Control::get_output(bool array[14]){
    
    for (int i = 0; i < 6; i++){
       signals[i] = alu_control[i];
    }

    signals[6] = alu_src;
    signals[7] = reg_dst;
    signals[8] = branch;
    signals[9] = mem_read;
    signals[10] = mem_wrt;
    signals[11] = mem_to_reg;
    signals[12] = reg_wrt;
    signals[13] = jump;

}

void Control::set_signals(bool arr[12]){
    for(int i = 0; i < 6; i++){
        alu_control[i] = arr[i];
    }
}

