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

r_type_inst create_r_type_inst(
    bool arr[32]
){
    r_type_inst inst;

    for (int i = 0; i < 5; i++){

        inst.opcode[i] = arr[i];
        inst.rs[i] = arr[6 + i];
        inst.rt[i] = arr[11 + i];
        inst.rd[i] = arr[16 + i];
        inst.shamt[i] = arr[21 + i];
        inst.func[i] = arr[26 + i];

        inst.full[i] = inst.opcode[i];
        inst.full[6 + i] = inst.rs[i];
        inst.full[11 + i] = inst.rt[i];
        inst.full[16 + i] = inst.rd[i];
        inst.full[21 + i] = inst.shamt[i];
        inst.full[26 + i] = inst.func[i];
        
    }

    inst.opcode[5] = arr[5];
    inst.func[5] = arr[31];

    inst.int_opcode = bin_to_int(inst.opcode, 6);
    inst.int_rs = bin_to_int(inst.rs, 5);
    inst.int_rt = bin_to_int(inst.rt, 5);
    inst.int_rd = bin_to_int(inst.rd, 5);
    inst.int_shamt = bin_to_int(inst.shamt, 5);
    inst.int_func = bin_to_int(inst.func, 6);

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

immediate_inst create_immediate_inst(
    bool arr[32]
){
    immediate_inst inst;
    
    for (int i = 0; i < 16; i++){
        if (i < 5){
            inst.opcode[i] = arr[i];
            inst.rs[i] = arr[6 + i];
            inst.rt[i] = arr[11 + i];

            inst.full[i] = inst.opcode[i];
            inst.full[6 + i] = inst.rs[i];
            inst.full[11 + i] = inst.rt[i];
        }
        inst.imm[i] = arr[i + 16];
        inst.full[16 + i] = inst.imm[i];
    }

    inst.opcode[5] = arr[5];

    inst.int_opcode = bin_to_int(inst.opcode, 6);
    inst.int_rs = bin_to_int(inst.rs, 5);
    inst.int_rt = bin_to_int(inst.rt, 5);
    inst.int_imm = bin_to_int(inst.imm, 16);

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

    for (int i = 0; i < 26; i++){
        if (i < 6){
            inst.full[i] = inst.opcode[i];
        }
        inst.full[6 + i] = inst.target[i];
    }

    return inst;
}

jump_inst create_jump_inst(
    bool arr[32]
){
    jump_inst inst;

    for (int i = 0; i < 26; i++){
        if (i < 6){
            inst.opcode[i] = arr[i];
            inst.full[i] = inst.opcode[i];
        }
        inst.target[i] = arr[i + 6];
        inst.full[6 + i] = inst.target[i];
    }

    inst.int_opcode = bin_to_int(inst.opcode, 6);
    inst.int_target = bin_to_int(inst.target, 26);

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

/*
INSTRUCTIONS
opcode 6 bits, function code 6 bits

128 unique insts
64 rtype
64 imm/jump

ALU:_________________________
rtypes:
1.ADD   0| Op: 000000 | func: 10|0000 rd//
2.ADDU  1| Op: 000000 | func: 10|0001 rd/
3.AND   4| Op: 000000 | func: 10|0100 rd//
4.NOR   7| Op: 000000 | func: 10|0111 rd//
5.OR    5| Op: 000000 | func: 10|0101 rd//
6.SLT  10| Op: 000000 | func: 10|1010 rd//
7.SLTU 11| Op: 000000 | func: 10|1011 rd/
8.SUB   2| Op: 000000 | func: 10|0010 rd//
9.SUBU  3| Op: 000000 | func: 10|0011 rd/
10.XOR  6| Op: 000000 | func: 10|0110 rd//

imm:
11.ADDI 8| Op: 001000 rt//
12.ADDIU9| Op: 001001 rt/   
13.ANDI12| Op: 001100 rt//
14.LUI 15| Op: 001111 rt//
15.ORI 13| Op: 001101 rt//
16.SLTI  | Op: 001010 rt//
17.SLTIU | Op: 001011 rt/
18.XORI14| Op: 001110 rt//
Shifter:______________________________
rtype:oo00
19.SLL   | Op: 000000 | func: 000|000 rd//
20.SLLV  | Op: 000000 | func: 000|100 rd//
21.SRA   | Op: 000000 | func: 000|011 rd//
22.SRAV  | Op: 000000 | func: 000|111 rd//
23.SRL   | Op: 000000 | func: 000|010 rd/
24.SRLV  | Op: 000000 | func: 000|110 rd/
Branch:______________________________
imm:
25.BEQ  4| Op: 000100 pc 3-5 zeros//
26.BGEZ 1| Op: 000001 pc/
27.BGEZA1| Op: 000001 pc/
28.BGTZ 7| Op: 000111 //
29.BLEZ 6| Op: 000110//
30.BLTZ 1| Op: 000001 /
31.BLTZA1| Op: 000001/
32.BNE  5| Op: 000101//

jump:
33.J     | Op: 000010//
34.JAL   | Op: 000011 4-zeros/

rtype:
35.JALR  | Op: 000000 | func: 001001 rd//
36.JR    | Op: 000000 | func: 001000   //

unknown:
37.BREAK | Op: 000000 | func: 001101 
38.MFC0  | Op: 010000 | func: 
39.MTC0  | Op: 010000 r1 zero
40.SYSCAL| Op: 000000 | func: 001100 f2 zeros

memacess:___________________________
imm:
41.LB    | Op: 100000//
42.LBU   | Op: 100100//
43.LH    | Op: 100001//
44.LHU   | Op: 100101//
45.LW    | Op: 100011//
46.SB    | Op: 101000//
47.SH    | Op: 101001//
48.SW    | Op: 101011//
*/

/*TO DO:
1. Add pseudo instructions
2. Increase Ram size
3. Add "External" Storage
4. Add Display capabilities
5. Run a program.
*/
