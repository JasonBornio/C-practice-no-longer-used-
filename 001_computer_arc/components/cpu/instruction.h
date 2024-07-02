#include "utilities.h"

typedef struct r_type_inst{
    bool opcode[6];
    bool rs[5];
    bool rt[5];
    bool rd[5];
    bool shamt[5];
    bool func[6];
    bool full[32];

    int int_opcode;
    int int_rs;
    int int_rt;
    int int_rd;
    int int_shamt;
    int int_func;
};

typedef struct immediate_inst{
    bool opcode[6];
    bool rs[5];
    bool rt[5];
    bool imm[16];
    bool full[32];

    int int_opcode;
    int int_rs;
    int int_rt;
    int int_imm;
};

typedef struct jump_inst{
    bool opcode[6];
    bool target[26];
    bool full[32];

    int int_opcode;
    int int_target;
};

r_type_inst create_r_type_inst(
    int opcode,
    int rs,
    int rt, 
    int rd,
    int shamt,
    int func
){
    r_type_inst inst;

    int_to_bin(opcode, inst.opcode, 6);
    int_to_bin(rs, inst.rs, 5);
    int_to_bin(rt, inst.rt, 5);
    int_to_bin(rd, inst.rd, 5);
    int_to_bin(shamt, inst.shamt, 5);
    int_to_bin(func, inst.func, 6);

    inst.int_opcode = opcode;
    inst.int_rs = rs;
    inst.int_rt = rt;
    inst.int_rd = rd;
    inst.int_shamt = shamt;
    inst.int_func = func;

    for (int i = 0; i < 5; i++){
        inst.full[i] = inst.opcode[i];
        inst.full[6 + i] = inst.rs[i];
        inst.full[11 + i] = inst.rt[i];
        inst.full[16 + i] = inst.rd[i];
        inst.full[21 + i] = inst.shamt[i];
        inst.full[26 + i] = inst.func[i];
    }

    inst.full[5] = inst.opcode[5];
    inst.full[31] = inst.func[5];

    return inst;
}

immediate_inst create_immediate_inst(
    int opcode,
    int rs,
    int rt, 
    int imm
){
    immediate_inst inst;

    int_to_bin(opcode, inst.opcode, 6);
    int_to_bin(rs, inst.rs, 5);
    int_to_bin(rt, inst.rt, 5);
    int_to_bin(imm, inst.imm, 16);

    inst.int_opcode = opcode;
    inst.int_rs = rs;
    inst.int_rt = rt;
    inst.int_imm = imm;

    for (int i = 0; i < 16; i++){
        if (i < 5){
            inst.full[i] = inst.opcode[i];
            inst.full[6 + i] = inst.rs[i];
            inst.full[11 + i] = inst.rt[i];
        }
        inst.full[16 + i] = inst.imm[i];
    }

    inst.full[5] = inst.opcode[5];

    return inst;
}

jump_inst create_jump_inst(
    int opcode,
    int target
){
    jump_inst inst;

    int_to_bin(opcode, inst.opcode, 6);
    int_to_bin(target, inst.target, 26);
        
    inst.int_opcode = opcode;
    inst.int_target = target;

    for (int i = 0; i < 16; i++){
        if (i < 6){
            inst.full[i] = inst.opcode[i];
        }
        inst.full[6 + i] = inst.target[i];
    }

    return inst;
}

void print_r_type_inst(r_type_inst inst){

    
    std::cout <<"r-type: ";

    std::cout <<" |opcode:" << inst.int_opcode << ", ";
    for (int i = 0; i < 6; i++){
        std::cout << int(inst.opcode[i]);
    }

    std::cout <<"|rs:" << inst.int_rs << ", ";
    for (int i = 0; i < 5; i++){
        std::cout << int(inst.rs[i]);
    }

    std::cout <<"|rt:" << inst.int_rt << ", ";
    for (int i = 0; i < 5; i++){
        std::cout << int(inst.rt[i]);
    }

    std::cout <<"|rd:" << inst.int_rd << ", ";
    for (int i = 0; i < 5; i++){
        std::cout << int(inst.rd[i]);
    }

    std::cout <<"|shamt:" << inst.int_shamt << ", ";
    for (int i = 0; i < 5; i++){
        std::cout << int(inst.shamt[i]);
    }

    std::cout <<"|func:" << inst.int_func << ", ";
    for (int i = 0; i < 6; i++){
        std::cout << int(inst.func[i]);
    }


    std::cout <<"|" << std::endl;
}

void print_immediate_inst(immediate_inst inst){

    std::cout <<"   imm: ";

    std::cout <<" |opcode:" << inst.int_opcode << ", ";
    for (int i = 0; i < 6; i++){
        std::cout << int(inst.opcode[i]);
    }

    std::cout <<"|rs:" << inst.int_rs << ", ";
    for (int i = 0; i < 5; i++){
        std::cout << int(inst.rs[i]);
    }

    std::cout <<"|rt:" << inst.int_rt << ", ";
    for (int i = 0; i < 5; i++){
        std::cout << int(inst.rt[i]);
    }

    std::cout <<"|imm:" << inst.int_imm << ", ";
    for (int i = 0; i < 16; i++){
        std::cout << int(inst.imm[i]);
    }

    std::cout << "|" << std::endl;
}

void print_jump_inst(jump_inst inst){

    std::cout <<"  jump: ";

    std::cout <<" |opcode:" << inst.int_opcode << ", ";
    for (int i = 0; i < 6; i++){
        std::cout << int(inst.opcode[i]);
    }

    std::cout <<"|target:" << inst.int_target << ", ";
    for (int i = 0; i < 26; i++){
        std::cout << int(inst.target[i]);
    }

    std::cout << "|" << std::endl;
}