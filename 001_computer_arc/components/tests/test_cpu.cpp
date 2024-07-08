#include "../cpu.h";
#include <stdio.h>

int main(){

    Cpu cpu;

    //add 
    immediate_inst inst1 = create_immediate_inst(8, 0, 2, 600);
    //add 
    immediate_inst inst2 = create_immediate_inst(8, 0, 3, 32767);
    //store
    immediate_inst inst3 = create_immediate_inst(43, 0, 2, 516);
    //load
    immediate_inst inst4 = create_immediate_inst(35, 0, 4, 516);

    //add
    r_type_inst inst5 = create_r_type_inst(0, 2, 3, 5, 0, 32);
    //and
    r_type_inst inst6 = create_r_type_inst(0, 2, 3, 6, 0, 36);
    //or
    r_type_inst inst7 = create_r_type_inst(0, 2, 3, 7, 0, 37);
    //nor
    r_type_inst inst8 = create_r_type_inst(0, 2, 3, 8, 0, 39);
    //xor
    r_type_inst inst9 = create_r_type_inst(0, 2, 3, 9, 0, 38);

    jump_inst inst10 = create_jump_inst(2, 16);

    bool instructions[10][32] = {};
    for (int i = 0; i < 32; i++){
        instructions[0][i] = inst1.full[i];
        instructions[1][i] = inst2.full[i];
        instructions[2][i] = inst3.full[i];
        instructions[3][i] = inst4.full[i];
        instructions[4][i] = inst5.full[i];
        instructions[5][i] = inst6.full[i];
        instructions[6][i] = inst7.full[i];
        instructions[7][i] = inst8.full[i];
        instructions[8][i] = inst9.full[i];
        instructions[9][i] = inst10.full[i];
    }

    cpu.load_instructions(instructions, 10);
    //cpu.print_instructions();
    //cpu.print_registers();

    cpu.execute_instructions(40);
    
    cpu.print_registers();

    cpu.print_data();

} 
