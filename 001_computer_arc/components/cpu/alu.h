#include "shifter.h"

class Arithmetic_Logic_Unit {
    public:
        Arithmetic_Logic_Unit();

        void clock_step(Reg_32 A, Reg_32 B, bool control[6], bool opcode[6], bool shift_amount[5]);
        Reg_32 get_output();
        bool zero();

    private:
        Adder_32 adder;
        Subtractor_32 subtractor;
        Shifter shifter;
        Reg_32 output;
        Reg_32 zero_reg;
        Reg_32 one_reg;
        bool _zero;
        bool buffer[32];
        bool shamt[32];
        bool reg_wrt;
        bool rd[5];
};

Arithmetic_Logic_Unit::Arithmetic_Logic_Unit(){
    zero_reg.clear();
    one_reg.clear();
    one_reg.fill_ones_lower(1);
    _zero = false;
    reg_wrt = false;
}

void Arithmetic_Logic_Unit::clock_step(Reg_32 A, Reg_32 B, bool control[6], bool opcode[6], bool shift_amount[5]){
    
    bool code[4];
    bool _ctrl[4]; 
    for (int i = 0; i < 4; i++){
        code[i] = opcode[i+2];
        _ctrl[i] = control[i+2];
    }

    int op =  bin_to_int(code, 4);
    int _op = bin_to_int(opcode, 6);
    int ctrl = bin_to_int(_ctrl, 4);

    _zero = false;

    //immm alu
    if(_op){
        switch(op){
            case 0: 
                if(opcode[0]){
                    //lb
                    std::cout<<"::::::::::LB"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //
                }
                break; 
            case 1: 
            if(opcode[0]){
                //lh
                std::cout<<"::::::::::LH"<<std::endl;
                output = adder.add(A, B);
            }
            else{
                //bgez, bgezal, blezal, bltz
                std::cout<<"::::::::::BRANCH"<<std::endl;
            }
                break;
            case 2: 
                //j
                std::cout<<"::::::::::J"<<std::endl;
                output = zero_reg;
                break; 
            case 3: 
                if(opcode[0]){
                    //lw
                    std::cout<<"::::::::::LW"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //jal
                    std::cout<<"::::::::::JAL"<<std::endl;
                    output = zero_reg;
                }
                break; 
            case 4: 
                if(opcode[0]){
                    //lbu
                    std::cout<<"::::::::::LBU"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //beq
                    if(A.get_data() == B.get_data()){
                        //std::cout<<"A: " << A.get_data() << ", B: " << B.get_data()<< std::endl;
                        std::cout<<"::::::::::BEQ"<<std::endl;
                        _zero = true;
                    }
                    output = zero_reg;
                }
                break;
            case 5: 
                if(opcode[0]){
                    //lhu
                    std::cout<<"::::::::::LHU"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //bne
                    if(A.get_data() != B.get_data()){
                        std::cout<<"::::::::::BNE"<<std::endl;
                        _zero = true;
                    }
                    output = zero_reg;
                }
                break;
            case 6: 
                //blez
                if(A.get_data() <= B.get_data()){
                    std::cout<<"::::::::::BLEZ"<<std::endl;
                    _zero = true;
                }
                output = zero_reg;
                break;
            case 7: 
                //bgtz
                if(A.get_data() > B.get_data()){
                    std::cout<<"::::::::::BGTZ"<<std::endl;
                    _zero = true;
                }
                output = zero_reg;
                break;
            case 8: 
                if(opcode[0]){
                    //sb
                    std::cout<<"::::::::::SB"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //addi
                    std::cout<<"::::::::::ADDI"<<std::endl;
                    output = adder.add(A, B);
                }
                break;
            case 9: 
                if(opcode[0]){
                    //sh
                    std::cout<<"::::::::::SH"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //addiu
                    std::cout<<"::::::::::ADDIU"<<std::endl;
                    output = adder.add(A, B);
                }
                break; 
            case 10: 
                //slti
                std::cout<<"::::::::::SLTI"<<std::endl;
                if (A.get_data() < B.get_data()){
                    output = one_reg;
                }else{
                    output = zero_reg;
                }
                break; 
            case 11: 
                if(opcode[0]){
                    //sw
                    std::cout<<"::::::::::SW"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //sltiu
                    std::cout<<"::::::::::SLTIU"<<std::endl;
                    if (A.get_data() < B.get_data()){
                        output = one_reg;
                    }else{
                        output = zero_reg;
                    }
                }
                break;
            case 12: 
                ////andi
                std::cout<<"::::::::::ANDI"<<std::endl;
                output = A & B;
                break;
            case 13: 
                //ori
                std::cout<<"::::::::::ORI"<<std::endl;
                output = A | B;
                break;
            case 14: 
                //xori
                std::cout<<"::::::::::XORI"<<std::endl;
                output = A ^ B;
                break;
            case 15: 
                //lui
                std::cout<<"::::::::::LUI"<<std::endl;
                int_to_bin(16, shamt, 32);
                B.get_data_arr(buffer);
                shifter.clock_step(buffer, shamt, 15);
                shifter.get_output(buffer);
                output.fill_arr_lower(buffer, 32);
                break;

            default:
                break; 
        }
    }
    //alu r_type
    else {
        switch(ctrl){
            case 0: 
                if (control[0]){
                    //add
                    std::cout<<"::::::::::ADD"<<std::endl;
                    output = adder.add(A, B);
                }
                else{
                    //sll
                    std::cout<<"::::::::::SLL"<<std::endl;
                    B.get_data_arr(buffer);
                    int_to_bin(bin_to_int(shift_amount, 5), shamt, 32);

                    shifter.clock_step(buffer, shamt, 0);
                    shifter.get_output(buffer);
                    output.fill_arr_lower(buffer, 32);
                }
                break;
            case 1: 
                //addu
                std::cout<<"::::::::::ADDU"<<std::endl;
                output = adder.add(A, B);
                break;
            case 2: 
                if(control[0]){
                    //sub
                    std::cout<<"::::::::::SUB"<<std::endl;
                    output = subtractor.sub(A, B);
                }
                else{
                    //srl
                    std::cout<<"::::::::::SRL"<<std::endl;
                    B.get_data_arr(buffer);
                    int_to_bin(bin_to_int(shift_amount, 5), shamt, 32);

                    shifter.clock_step(buffer, shamt, 2);
                    shifter.get_output(buffer);
                    output.fill_arr_lower(buffer, 32);
                }
                break;
            case 3: 
                if(control[0]){
                    //subu
                    std::cout<<"::::::::::SUBU"<<std::endl;
                    output = subtractor.sub(A, B);
                }
                else{
                    //sra
                    std::cout<<"::::::::::SRA"<<std::endl;
                    B.get_data_arr(buffer);
                    int_to_bin(bin_to_int(shift_amount, 5), shamt, 32);

                    shifter.clock_step(buffer, shamt, 3);
                    shifter.get_output(buffer);
                    output.fill_arr_lower(buffer, 32);
                }
                break;
            case 4: 
                if(control[0]){
                    //and
                    std::cout<<"::::::::::AND"<<std::endl;
                    output = A & B;
                }
                else{
                    //sllv
                    std::cout<<"::::::::::SLLV"<<std::endl;
                    B.get_data_arr(buffer);
                    A.get_data_arr(shamt);

                    shifter.clock_step(buffer, shamt, 4);
                    shifter.get_output(buffer);
                    output.fill_arr_lower(buffer, 32);
                }
                break;
            case 5:     
                //or
                std::cout<<"::::::::::OR"<<std::endl;
                output = A | B;
                break;
            case 6:
                if(control[0]){ 
                    //xor
                    std::cout<<"::::::::::XOR"<<std::endl;
                    output = A ^ B;
                }
                else{
                    //srlv
                    std::cout<<"::::::::::SRLV"<<std::endl;
                    B.get_data_arr(buffer);
                    A.get_data_arr(shamt);

                    shifter.clock_step(buffer, shamt, 6);
                    shifter.get_output(buffer);
                    output.fill_arr_lower(buffer, 32);
                }
                break;
            case 7: 
                if(control[0]){
                    //nor
                    std::cout<<"::::::::::NOR"<<std::endl;
                    zero_reg = A | B;
                    output = ~zero_reg;
                    zero_reg.clear();
                }
                else{
                    //srav
                    std::cout<<"::::::::::SRAV"<<std::endl;
                    B.get_data_arr(buffer);
                    A.get_data_arr(shamt);

                    shifter.clock_step(buffer, shamt, 7);
                    shifter.get_output(buffer);
                    output.fill_arr_lower(buffer, 32);
                }
                break;
            case 8: 
                //jr
                std::cout<<"::::::::::JR"<<std::endl;
                output = A;
                break;
            case 9: 
                //jalr
                std::cout<<"::::::::::JALR"<<std::endl;
                output = A;
                break;
            case 10: 
                //slt
                std::cout<<"::::::::::SLT"<<std::endl;
                if (A.get_data() < B.get_data()){
                    output = one_reg;
                }else{
                    output = zero_reg;
                }
                break;
            case 11: 
                //sltu
                std::cout<<"::::::::::SLTU"<<std::endl;
                if (A.get_data() < B.get_data()){
                    output = one_reg;
                }else{
                    output = zero_reg;
                }
                break;
            //branch

            //no alu
            case 15:
                output = zero_reg;
                break; 
            default:
                break; 
        }
    }
}

Reg_32 Arithmetic_Logic_Unit::get_output(){
    return output;
}

bool Arithmetic_Logic_Unit::zero(){
    return _zero;
}
