#include <iostream>
#include <iomanip>

class Programcounter {
    public:
        Programcounter();

        void increment();
        void branch(int offset);
        void jump(int address);
        int get_pc();

        void print();
 
    private:

        int text_pointers[2] = { 64, 508 };
        int pc;

};

Programcounter::Programcounter(){
    pc = text_pointers[0];
}

void Programcounter::increment(){
    pc += 4;
    if(pc > text_pointers[1]) pc = text_pointers[1];
}

void Programcounter::branch(int offset){
    pc += offset * 4;
    if(pc > text_pointers[1]) pc = text_pointers[1];
    if(pc < text_pointers[0]) pc = text_pointers[0];

}

void Programcounter::jump(int address){
    pc = address;

    if(pc > text_pointers[1]) pc = text_pointers[1];
    if(pc < text_pointers[0]) pc = text_pointers[0];
}

int Programcounter::get_pc(){
    return pc;
}

void Programcounter::print(){
    std::cout << "      PC: " << "0x" << std::setfill('0') << std::setw(3) << std::hex << pc << ", " << std::dec << pc << std::endl; 
}
