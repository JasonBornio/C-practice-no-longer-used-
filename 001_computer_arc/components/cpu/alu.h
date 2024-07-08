#include "programcounter.h"

class Arithmetic_Logic_Unit {
    public:
        Arithmetic_Logic_Unit();

        void clock_step(Reg_32 A, Reg_32 B, bool control[4], bool opcode[6]);
        Reg_32 get_output();
        bool zero();

    private:
        Adder_32 adder;
        Reg_32 output;
        Reg_32 zero_reg;
        bool _zero;

};

Arithmetic_Logic_Unit::Arithmetic_Logic_Unit(){
    zero_reg.clear();
    _zero = false;
}

void Arithmetic_Logic_Unit::clock_step(Reg_32 A, Reg_32 B, bool control[4], bool opcode[6]){

    int ctrl = bin_to_int(control, 4);
    bool code[4];
    for (int i = 0; i < 4; i++){
        code[i] = opcode[i+2];
    }

    int op =  bin_to_int(code, 4);

    if (opcode[0]){
        output = adder.add(A, B);
    }
    //immm alu
    else if(op && ctrl < 15){
        switch(op){
            case 8: 
                //addi
                std::cout<<"::::::::::ADDI"<<std::endl;
                output = adder.add(A, B);
                break;
            case 9: 
                //addiu
                std::cout<<"::::::::::ADDIU"<<std::endl;
                output = adder.add(A, B);
                break; 
            case 10: 
                //slti
                std::cout<<"::::::::::SLTI"<<std::endl;
                output = output;//A & B;
                break; 
            case 11: 
                //sltiu
                std::cout<<"::::::::::SLTIU"<<std::endl;
                output = output;//A & B;
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
                output = output;//A & B;
                break;

            default:
                break; 
        }
    }
    //alu r_type
    else {
        switch(ctrl){
            case 0: 
                //add
                std::cout<<"::::::::::ADD"<<std::endl;
                output = adder.add(A, B);
                break;
            case 1: 
                //addu
                std::cout<<"::::::::::ADDU"<<std::endl;
                output = adder.add(A, B);
                break;
            case 2: 
                //sub
                std::cout<<"::::::::::SUB"<<std::endl;
                output = output;//A & B;
                break;
            case 3: 
                //subu
                std::cout<<"::::::::::SUBU"<<std::endl;
                output = output;//A & B;
                break;
            case 4: 
                //and
                std::cout<<"::::::::::AND"<<std::endl;
                output = A & B;
                break;
            case 5:     
                //or
                std::cout<<"::::::::::OR"<<std::endl;
                output = A | B;
                break;
            case 6: 
                //xor
                std::cout<<"::::::::::XOR"<<std::endl;
                output = A ^ B;
                break;
            case 7: 
                //nor
                std::cout<<"::::::::::NOR"<<std::endl;
                zero_reg = A | B;
                output = ~zero_reg;
                zero_reg.clear();
                break;
            case 10: 
                //slt
                std::cout<<"::::::::::SLT"<<std::endl;
                output = output;//A & B;
                break;
            case 11: 
                //sltu
                std::cout<<"::::::::::SLTU"<<std::endl;
                output = output;//A & B;
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
