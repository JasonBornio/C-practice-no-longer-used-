#include <iostream>
#include <iomanip>
#include "control.h"

class Program_Counter {
    public:
        Program_Counter();

        void increment();
        void branch(bool offset[32]);
        void jump(bool address[32]);
        void get_pc(bool arr[32]);

        void print();
 
    private:

        int text_pointers[2] = { 64, 508 };
        Reg_32 pc;
        Adder_32 adder;
        

};

Program_Counter::Program_Counter(){
    bool arr[32];
    int_to_bin(text_pointers[0], arr, 32);
    pc.fill_arr_lower(arr, 32);
}

void Program_Counter::increment(){
    pc = adder.add_int(pc, 4);
    if(pc.get_data() > text_pointers[1]){
        bool arr[32];
        int_to_bin(text_pointers[1], arr, 32);
        pc.fill_arr_lower(arr, 32);
    }
}

void Program_Counter::branch(bool offset[32]){

    pc = adder.add_int(pc, (bin_to_int(offset, 32) * 4));

    if(pc.get_data() > text_pointers[1]){
        bool arr[32];
        int_to_bin(text_pointers[1], arr, 32);
        pc.fill_arr_lower(arr, 32);
    }
    if(pc.get_data() < text_pointers[0]){
        bool arr[32];
        int_to_bin(text_pointers[0], arr, 32);
        pc.fill_arr_lower(arr, 32);
    }

}

void Program_Counter::jump(bool address[32]){
    pc.fill_arr_lower(address, 32);

    if(pc.get_data() > text_pointers[1]){
        bool arr[32];
        int_to_bin(text_pointers[1], arr, 32);
        pc.fill_arr_lower(arr, 32);
    }
    if(pc.get_data() < text_pointers[0]){
        bool arr[32];
        int_to_bin(text_pointers[0], arr, 32);
        pc.fill_arr_lower(arr, 32);
    }
}

void Program_Counter::get_pc(bool arr[32]){
    for(int i = 0; i < 32; i++){
        arr[i] = pc.get_data(i);
    }
}

void Program_Counter::print(){
    std::cout << "      PC: " << "0x" << std::setfill('0') << std::setw(3) << std::hex << pc.get_data() << ", " << std::dec << pc.get_data() << std::endl; 
}
