#include "programcounter.h"

class Shifter {
    public:
        Shifter();
        
        void clock_step(bool arr[32], bool shamt[32], int ctrl);
        void shift(bool arr[32]);
        void get_output(bool array[32]);

        void shift_left(bool arr[32], int num);
        void shift_right(bool arr[32], int num);

        void print();

    private:
        
        bool output[32] = {};

};

Shifter::Shifter(){

}

void Shifter::clock_step(bool arr[32], bool shamt[32], int ctrl){
    int shift_amount = bin_to_int(shamt, 32);
    std::cout<< shift_amount<<std::endl;

    switch(ctrl){
        case 0:
            shift_left(arr, shift_amount);
            break;
        case 2:
            shift_right(arr, shift_amount);
            break;
        case 3:
            shift_right(arr, shift_amount);
            break;        
        case 4:
            shift_left(arr, shift_amount);
            break;        
        case 6:
            shift_right(arr, shift_amount);
            break;        
        case 7:
            shift_right(arr, shift_amount);
            break;        
        default:
            shift_left(arr, shift_amount);
            break;
    }
}

void Shifter::shift_left(bool arr[32], int num){

    int size = 32 - num;
    
    for(int i = 0; i < size; i++){
        output[i] = arr[i + num];
    }
    for(int i = 0; i < num; i++){
        output[i + size] = false;
    }
}

void Shifter::shift_right(bool arr[32], int num){

    int size = 32 - num;
    
    for(int i = 0; i < size; i++){
        output[i + num] = arr[i];
    }
    for(int i = 0; i < num; i++){
        output[i] = false;
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
