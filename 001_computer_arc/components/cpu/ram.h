#include <iostream>
#include <iomanip>
#include "adder.h"

class Random_Access_Memory {
    public:

        Random_Access_Memory();

        void data_clk_step(bool _address[32], bool write_data[32], bool _mem_wrt, bool _mem_read);
        void inst_clk_step(bool _address[32]);
        void get_data_out(bool arr[32]);
        void load_instructions(bool arr[][32], int length);
        int get_top_inst_pointer();

        void print(int num);
        void print_data();
        void print_instructions();
        void print_stack();

    private:

        bool memory[1024][8] = {};

        int reserved_pointer = 0;
        int text_pointers[3] = { 64, 508, 64 };  //448 wide (112 words)
        int static_data_pointers[2] = { 512, 767 }; //256 wide (64 words)
        int dynamic_data_pointers[2] = { 768, 768 };
        int stack_pointer = 1024;

        //inputs
        bool mem_write;
        bool mem_read;
        bool data_in[32] = {};
        int address;

        //outputs
        bool data_out[32] = {};

        void write_data(int address, bool data[8]);
        void read_data(int address, bool arr[8]);
        void write_word(int address, bool data[32]);
        void read_word(int address, bool arr[32]);

        void print(int lower_bound, int upper_bound);

};

Random_Access_Memory::Random_Access_Memory(){
    address = 0;
}

void Random_Access_Memory::write_data(int address, bool data[8]){
    for(int i = 0; i < 8; i ++){
        memory[address][i] = data[i];
    }
}

void Random_Access_Memory::read_data(int address, bool arr[8]){
    for(int i = 0; i < 8; i ++){
        arr[i] = memory[address][i];
    }
}

void Random_Access_Memory::write_word(int address, bool data[32]){
    for(int i = 0; i < 8; i++){
        memory[address+ 3][i] = data[i];
        memory[address + 2][i] = data[i + 8];
        memory[address + 1][i] = data[i + 16];
        memory[address][i] = data[i + 24];
    }
}

void Random_Access_Memory::read_word(int address, bool arr[32]){
    for(int i = 0; i < 8; i ++){
        arr[i] = memory[address + 3][i];
        arr[i + 8] = memory[address + 2][i];
        arr[i + 16] = memory[address + 1][i];
        arr[i + 24] = memory[address][i];
    }
}

void Random_Access_Memory::data_clk_step(bool _address[32], bool write_data[32], bool _mem_wrt, bool _mem_read){
    mem_write = _mem_wrt;
    mem_read = _mem_read;
    address = bin_to_int(_address, 32);

    //std::cout<<"ADRESS"<< address<< std::endl;
    
    for (int i = 0; i < 32; ++i) {
        data_in[i] = write_data[i];
    }

    if(mem_write)
        write_word(address, data_in);

    if(mem_read)
        read_word(address, data_out);
}

void Random_Access_Memory::inst_clk_step(bool _address[32]){
    
    address = bin_to_int(_address, 32);

    if(address > text_pointers[1]) address = text_pointers[1];
    if(address < text_pointers[0]) address = text_pointers[0];

    read_word(address, data_out);

}

void Random_Access_Memory::get_data_out(bool arr[32]){
    for (int i = 0; i < 32; ++i) {
        arr[i] = data_out[i];
    }
}

void Random_Access_Memory::load_instructions(bool arr[][32], int length){

    for (int i = 0; i < length; i++){
        if(text_pointers[2] > text_pointers[1]){
            break;
        }
        write_word((i * 4) + text_pointers[2], arr[i]);
    }
    
    text_pointers[2] += length * 4;
    
    if(text_pointers[2] > text_pointers[1]) text_pointers[2] = text_pointers[1] + 4;

}

int Random_Access_Memory::get_top_inst_pointer(){
    return text_pointers[2];
}

void Random_Access_Memory::print(int lower_bound, int upper_bound){
    for(int i = lower_bound; i < upper_bound; i++){

        std::cout << "0x" << std::setfill('0') << std::setw(3) << std::hex << i << std::dec <<": { ";

        for (int j = 0; j < 8; j++){
            std::cout << int(memory[i][j]);
        }

        std::cout <<", val: "<< bin_to_int(memory[i], 8)  << " }"<< std::endl;
    }
}

void Random_Access_Memory::print(int num){

    if (num > 1024) num = 1024;

    std::cout << "      ram::" << std::endl;
    print(0, num);
    
}

void Random_Access_Memory::print_data(){
    
    std::cout << "stat-data::" << std::endl;
    print(static_data_pointers[0], static_data_pointers[1]);

    std::cout << "dyna-data::" << std::endl;
    print(dynamic_data_pointers[0], dynamic_data_pointers[1]);
    
}

void Random_Access_Memory::print_instructions(){
    
    std::cout << "instructs::" << std::endl;
    print(text_pointers[0], text_pointers[1]);
    
}

void Random_Access_Memory::print_stack(){
    
    std::cout << "    stack::" << std::endl;
    print(stack_pointer, 1024);
    
}
