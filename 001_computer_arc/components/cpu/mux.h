#include "utilities.h"

class Multiplexer_2 {
    public:
        Multiplexer_2();

        void clock_step(bool inputs[][32], int num_inputs, bool control_signal[2]);
        void get_output(bool array[32]);

        void print();

    private:

        bool current_output[32] = {};


};

Multiplexer_2::Multiplexer_2(){

}

void Multiplexer_2::clock_step(bool inputs[][32], int num_inputs, bool control_signal[2]){

    int index = bin_to_int(control_signal, 2);

    if (index > num_inputs-1) index = num_inputs-1;

    for(int i = 0; i < 32; i++){
        current_output[i] = inputs[index][i];
    }

}

void Multiplexer_2::get_output(bool array[32]){
    for(int i = 0; i < 32; i++){
        array[i] = current_output[i];
    }
}

void Multiplexer_2::print(){
    std::cout <<"  output: { ";

    for (int i = 0; i < constants::g_dim; i++){
        std::cout << int(current_output[i]);
    }

    std::cout <<", val: "<< bin_to_int(current_output, 32) << " }"<< std::endl;
}
