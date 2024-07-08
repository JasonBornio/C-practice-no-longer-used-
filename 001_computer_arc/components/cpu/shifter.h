#include "programcounter.h"

class Shifter {
    public:
        Shifter();
        
        void clock_step(bool arr[32], bool shamt[5]);
        void shift(bool arr[32]);
        void get_output(bool array[32]);

        void print();

    private:
        
        bool output[32] = {};

};

Shifter::Shifter(){

}

void Shifter::clock_step(bool arr[32], bool shamt[5]){
    int shift_amount = bin_to_int(shamt, 5);
    int size = 32 - shift_amount;

    for(int i = 0; i < size; i++){
        output[i] = arr[i + shift_amount];
    }
    for(int i = 0; i < shift_amount; i++){
        output[i + size] = false;
    }

}

void Shifter::shift(bool arr[32]){
    for(int i = 0; i < 30; i++){
        output[i] = arr[i+2];
    }

    output[30] = false;
    output[31] =  false;
}

void Shifter::get_output(bool array[32]){
    for(int i = 0; i < 32; i++){
        array[i] = output[i];
    }
}

void Shifter::print(){
    std::cout <<"  output: { ";

    for (int i = 0; i < 32; i++){
        std::cout << int(output[i]);
    }

    std::cout <<", val: "<< bin_to_int(output, 32) << " }"<< std::endl;
}