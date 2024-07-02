#include "utilities.h"

class Multiplexer_2 {
    public:
        Multiplexer_2();

        void clock_step(bool inputs[4][32]);
        void get_output(bool control_signal[2], bool array[32]);

        void print();

    private:

        bool current_inputs[4][32] = {};
        bool current_output[32] = {};
        int num_inputs = 0;


};

Multiplexer_2::Multiplexer_2(){

}

void Multiplexer_2::clock_step(bool inputs[4][32]){
    for(int i = 0; i < 32; i++){
        current_inputs[0][i] = inputs[0][i];
        current_inputs[1][i] = inputs[1][i];
        current_inputs[2][i] = inputs[2][i];
        current_inputs[3][i] = inputs[3][i];
    }
}

void Multiplexer_2::get_output(bool control_signal[2], bool array[32]){

    int index = bin_to_int(control_signal, 2);

    for(int i = 0; i < 32; i++){
        array[i] = current_inputs[index][i];
        current_output[i] = current_inputs[index][i];
    }
}

void Multiplexer_2::print(){
    std::cout <<"  output: { ";

    for (int i = 0; i < constants::g_dim; i++){
        std::cout << int(current_output[i]);
    }

    std::cout <<", val: "<< bin_to_int(current_output, 32) << " }"<< std::endl;
}
