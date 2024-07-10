#include "../assembler.h"

#include <fstream>
#include <iostream>
#include <string>


int main(){
    Cpu cpu;
    Assembler assembler(cpu);

    assembler.load_file("assembly.txt", false);
    assembler.show_instructions(false);
    
    assembler.run(100, false);
    assembler.show_registers(true);
    assembler.show_ram_data(false);

    return 0;
} 
