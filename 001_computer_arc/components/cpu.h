#include "cpu/alu.h"
#include "cpu/signextend.h"

class Cpu {
    public:
        Cpu();

        void clock_step();

        void instruction_fetch();
        void instruction_decode();
        void execute();
        void memory_acess();
        void write_back();

    private:
        Reg_32 alu_a_reg;
        Reg_32 alu_b_reg;
        Reg_32 alu_out_reg;
        Reg_32 instruction_reg;

        Reg_32 if_id_reg[3];
        Reg_32 id_ex_reg[3];
        Reg_32 ex_mem_reg[3];
        Reg_32 mem_wb_reg[3];

        Program_Counter pc;
        Random_Access_Memory ram;
        Register_File registers;
        Arithmetic_Logic_Unit alu;
        Control control;
        Multiplexer_2 multiplexers[5];
        Sign_Extend sign_extend;

};

void Cpu::clock_step(){

}

void Cpu::instruction_fetch(){
    //ram.inst_clk_step(pc.get_pc())
    //instruction_reg.fill_ones_lower(ram.)
}

void Cpu::instruction_decode(){

}

void Cpu::execute(){

}
 
void Cpu::memory_acess(){

}

void Cpu::write_back(){

}