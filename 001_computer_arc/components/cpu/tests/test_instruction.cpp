#include "../instruction.h"

int main(){

    bool arr[32];

    r_type_inst inst1 = create_r_type_inst(35,25,8,9,0,4);
    print_r_type_inst(inst1);

    immediate_inst inst2 = create_immediate_inst(19, 22, 11, 31604);
    print_immediate_inst(inst2);

    jump_inst inst3 = create_jump_inst(30, 4350);
    print_jump_inst(inst3);

    int_to_bin(2000000000, arr, 32);
    inst1 = create_r_type_inst(arr);
    print_r_type_inst(inst1);

    int_to_bin(500000000, arr, 32);
    inst2 = create_immediate_inst(arr);
    print_immediate_inst(inst2);
    
    int_to_bin(1879000000, arr, 32);
    inst3 = create_jump_inst(arr);
    print_jump_inst(inst3);
} 
