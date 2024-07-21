#include "cpu/alu.h"

class Cpu {
    public:
        Cpu();

        void clock_step();

        void load_instructions(bool arr[][32], int length);
        void execute_instructions(int num);
        void execute_instructions();

        void print_registers();
        void print_pipeline_registers();
        void print_ram(int num);
        void print_data();
        void print_instructions();
        void print_control();

    private:

        //registers
        Reg_32 alu_a_reg;
        Reg_32 alu_b_reg;
        Program_Counter pc;


        //msb of last 3 regs are control signals
        //first 5 lsb of last 3 regs are rs rt rd.
        //pipeline registers
        Reg_32 if_id_reg[3] = {};
        Reg_32 id_ex_reg[5] = {};
        Reg_32 ex_mem_reg[4] = {};
        Reg_32 mem_wb_reg[3] = {};

        
        Random_Access_Memory ram;
        Register_File registers;
        Arithmetic_Logic_Unit alu;
        Control control;
        Multiplexer_2 multiplexers[5];
        Sign_Extend sign_extend;
        Adder_32 adder;
        Shifter shifters[2];

        bool pc_src;
        bool buffers[2][32];

        void instruction_fetch();
        void instruction_decode();
        void execute();
        void memory_acess();
        void write_back();
};

Cpu::Cpu(){
    mem_wb_reg[0].clear();
    mem_wb_reg[1].clear();
    mem_wb_reg[2].clear();
    pc_src = false;

    alu_a_reg.set_name("$alu_a");
    alu_b_reg.set_name("$alu_b");
    
    if_id_reg[0].set_name("$p_pc");
    if_id_reg[1].set_name("$p_instr");

    id_ex_reg[0].set_name("$p_pc");
    id_ex_reg[1].set_name("$p_rs");
    id_ex_reg[2].set_name("$p_rt");
    id_ex_reg[3].set_name("$p_[16:]");
    id_ex_reg[4].set_name("$p_ctrl");
    
    ex_mem_reg[0].set_name("$p_pc");
    ex_mem_reg[1].set_name("$p_alu_o");
    ex_mem_reg[2].set_name("$p_rd");
    ex_mem_reg[3].set_name("$p_ctrl");
    
    
    mem_wb_reg[0].set_name("$p_mem_o");
    mem_wb_reg[1].set_name("$p_alu_o");
    mem_wb_reg[2].set_name("$p_ctrl");
        
}

void Cpu::clock_step(){

    instruction_fetch();
    instruction_decode();
    execute();
    memory_acess();
    write_back();

}

void Cpu::execute_instructions(int num){
    int count = 0;
    while (pc.get_pc() <  ram.get_top_inst_pointer() + 4 && count < num){
        clock_step();
        //print_pipeline_registers();
        //print_registers();
        count += 1;
        //if (count < 32) print_pipeline_registers();
    }
}

void Cpu::execute_instructions(){
    while (pc.get_pc() <  ram.get_top_inst_pointer() + 4){
        clock_step();
    }
}

void Cpu::instruction_fetch(){

    bool arr_1[4][32];
    bool arr_2[4][32];
    bool ctrl[2] = { false, pc_src };
    
    //pc
    pc.get_pc(buffers[0]);
    
    //fill old_pc register
    if_id_reg[2].fill_arr_lower(buffers[0], 32);

    //branch mux0 set inputs (pc, branch)
    for(int i = 0; i < 32; i++){
        arr_1[0][i] = buffers[0][i];
        arr_1[1][i] = ex_mem_reg[0].get_data(i);
    }

    //get mux0 output
    multiplexers[0].clock_step(arr_1);
    multiplexers[0].get_output(ctrl, buffers[0]);

    //target 26-bits
    id_ex_reg[3].get_data_arr(buffers[1]);

    //shifter0 shift target left by 2
    shifters[0].shift(buffers[1]);
    shifters[0].get_output(buffers[1]);

    //jump mux1 set inputs (mux0, target, target, rs)
    for (int i = 0; i < 32; i ++){
        arr_2[0][i] = buffers[0][i];
        arr_2[1][i] = buffers[1][i];
        arr_2[2][i] = buffers[1][i]; //need to do
        arr_2[3][i] = id_ex_reg[1].get_data(i);
    }

    //jump ctrl____________________________________________DO_
    ctrl[0] = ex_mem_reg[3].get_data(9);
    ctrl[1] = ex_mem_reg[3].get_data(10);

    //get mux1 output
    multiplexers[1].clock_step(arr_2);
    multiplexers[1].get_output(ctrl, buffers[0]);

    //set pc
    pc.jump(buffers[0]);

    //get intructin at pc
    ram.inst_clk_step(buffers[0]);
    
    //fill instruction register
    ram.get_data_out(buffers[0]);
    if_id_reg[1].fill_arr_lower(buffers[0], 32);
    
    //pc += 4
    pc.increment();

    //fill pc register
    pc.get_pc(buffers[0]);
    if_id_reg[0].fill_arr_lower(buffers[0], 32);
    
}

void Cpu::instruction_decode(){

    //fill pc register
    id_ex_reg[0].copy(if_id_reg[0]);
        
    //decode inst
    bool opcode[6];
    bool func[6];
    bool op_current = false;
    bool jump = true;
    bool r_type = true;

    //get instruction
    if_id_reg[1].get_data_arr(buffers[0]);

    //get opcode
    for (int i = 0; i < 6; i++){
        op_current = buffers[0][i];
        func[i] = buffers[0][i+26];
        
        opcode[i] = op_current;

        if(op_current){
            //check for r_type or jump
            r_type = false;
            if(i < 4) jump = false;
        }
    }

    //decode the instruction
    if(jump && opcode[4]){
        //jump target intruction:
        //std::cout<<"Jump"<<std::endl;
        jump_inst instruction = create_jump_inst(buffers[0]);
        id_ex_reg[3].fill_arr_lower(instruction.target, 26);
    }
    else if (r_type){
        //rtype:
        //std::cout<<"R"<<std::endl;
        r_type_inst instruction = create_r_type_inst(buffers[0]);

        registers.clk_step(
            instruction.int_rs,
            instruction.int_rt,
            31,
            buffers[0],
            false
        );

        //get registers
        registers.get_rs(buffers[0]);
        registers.get_rt(buffers[1]);
        id_ex_reg[1].fill_arr_lower(buffers[0], 32);
        id_ex_reg[2].fill_arr_lower(buffers[1], 32);

        id_ex_reg[3].fill_arr_upper(instruction.shamt, 5);
        
        id_ex_reg[4].fill_arr_lower(instruction.rt, 5);
        id_ex_reg[4].fill_arr_lower(instruction.rd, 5, 5);
    }
    else{
        //imm
        //std::cout<<"IMM"<<std::endl;
        immediate_inst instruction = create_immediate_inst(buffers[0]);

        registers.clk_step(
            instruction.int_rs,
            instruction.int_rt,
            31,
            buffers[0],
            false
        );

        //get registers
        registers.get_rs(buffers[0]);
        registers.get_rt(buffers[1]);
        id_ex_reg[1].fill_arr_lower(buffers[0], 32);
        id_ex_reg[2].fill_arr_lower(buffers[1], 32);

        sign_extend.extend_half(instruction.imm);
        sign_extend.get_output(buffers[0]);
        
        id_ex_reg[3].fill_arr_lower(buffers[0], 32);
        id_ex_reg[4].fill_arr_lower(instruction.rt, 5);
    }

    //set control signals
    bool signals[22];
    control.set_signals(opcode, func);
    control.get_output(signals);
    id_ex_reg[4].fill_arr_upper(signals, 22);

    // std::cout<<"opfunc:: ";
    // print_bin(opcode, 6);
    // print_bin(func, 6);
    // std::cout<<"signal:: ";
    // print_bin(signals, 19);

}

void Cpu::execute(){

    //mux inputs
    bool arr_1[4][32] = {};
    bool arr_2[4][32] = {};
    
    //alu inputs
    bool alu_ctrl[6];
    bool alu_op[6];
    bool alu_shamt[5];

    //get and shift offset
    id_ex_reg[3].get_data_arr(buffers[0]);

    //shifter1
    shifters[1].shift(buffers[0]);
    shifters[1].get_output(buffers[0]);

    //add offset to pc and fill pc register
    ex_mem_reg[0] = adder.add_int(id_ex_reg[0], bin_to_int(buffers[0], 32));
    ex_mem_reg[0].set_name("$p_pc");

    //rt register
    id_ex_reg[2].get_data_arr(arr_1[0]);
    //imm register
    id_ex_reg[3].get_data_arr(arr_1[1]);

    //mux2 (rt, imm)
    multiplexers[2].clock_step(arr_1);

    //alu_src
    bool ctrl[2] = {false, id_ex_reg[4].get_data(12)};
    multiplexers[2].get_output(ctrl, buffers[0]);

    //fill alu A and B registers
    id_ex_reg[1].get_data_arr(buffers[1]);
    alu_a_reg.fill_arr_lower(buffers[1], 32);
    alu_b_reg.fill_arr_lower(buffers[0], 32);

    //get alu input signals
    for (int i = 0; i < 6; i++){
        alu_ctrl[i] = id_ex_reg[4].get_data(i);
        alu_op[i] = id_ex_reg[4].get_data(i+6);
        if(i < 5)
            alu_shamt[i] = id_ex_reg[3].get_data(i);
    }

    // std::cout<<"alu_ctrl:: ";
    // print_bin(alu_ctrl, 4);
    // std::cout<<"alu_op :: ";
    // print_bin(alu_op, 6);

    //compute alu function 
    alu.clock_step(alu_a_reg, alu_b_reg, alu_ctrl, alu_op, alu_shamt);

    //fill alu_out register
    ex_mem_reg[1].copy(alu.get_output());

    //fill data register
    ex_mem_reg[2].copy(id_ex_reg[2]);

    //mux3 inputs (rd, rt)
    for (int i = 0; i < 5; i++){
        arr_2[0][27+i] = id_ex_reg[4].get_data(22+i);
        arr_2[1][27+i] = id_ex_reg[4].get_data(27+i);
    }

    //reg_dst
    multiplexers[3].clock_step(arr_2);
    ctrl[1] = id_ex_reg[4].get_data(13);

    //fill lower reg_dst register
    multiplexers[3].get_output(ctrl, buffers[0]);
    ex_mem_reg[3].fill_arr_lower(buffers[0], 32, 5);

    //control signals
    bool signals[13] = {
        id_ex_reg[4].get_data(8),  //op[2]
        id_ex_reg[4].get_data(9),  //op[3]
        id_ex_reg[4].get_data(10), //op[4]
        id_ex_reg[4].get_data(11), //op[5]
        id_ex_reg[4].get_data(14), //branch
        id_ex_reg[4].get_data(15), //mem_read
        id_ex_reg[4].get_data(16), //mem_write
        id_ex_reg[4].get_data(17), //mem_to_reg
        id_ex_reg[4].get_data(18), //reg_wrt
        id_ex_reg[4].get_data(19), //jump[0]
        id_ex_reg[4].get_data(20), //jump[1]
        id_ex_reg[4].get_data(21), //link
        alu.zero()

    };

    //fill upper reg_dst register
    ex_mem_reg[3].fill_arr_upper(signals, 13);
}
 
void Cpu::memory_acess(){

    bool ram_ctrl[3];
    ex_mem_reg[1].get_data_arr(buffers[0]);
    ex_mem_reg[2].get_data_arr(buffers[1]);

    //and gate
    pc_src = (ex_mem_reg[3].get_data(4)) && ex_mem_reg[3].get_data(12);

    //get ram control (op[2:5])
    for(int i = 0; i<3; i++){
        ram_ctrl[i] = ex_mem_reg[3].get_data(i + 1);
    }

    //memory access
    ram.data_clk_step(
        buffers[0],
        buffers[1],
        ex_mem_reg[3].get_data(6),
        ex_mem_reg[3].get_data(5),
        ram_ctrl
    );
    
    ram.get_data_out(buffers[0]);

    //fill memory out register
    mem_wb_reg[0].fill_arr_lower(buffers[0], 32);

    //fill alu out register
    mem_wb_reg[1].copy(ex_mem_reg[1]);

    //fill lower reg_dst register 
    ex_mem_reg[3].get_data_arr(buffers[1]);
    mem_wb_reg[2].fill_arr_lower(buffers[1], 32);

    //control signals
    bool signals[3] = {
        ex_mem_reg[3].get_data(7), //mem_to_reg
        ex_mem_reg[3].get_data(8), //reg_wrt
        ex_mem_reg[3].get_data(11) //link
    };

    //fill upper reg_dst register
    mem_wb_reg[2].fill_arr_upper(signals, 3);

}

void Cpu::write_back(){
    bool arr[4][32];
    bool write_reg_bin[5];
    int write_reg = 31;

    //mux4 inputs (mem_out, alu_out, pc, pc)
    mem_wb_reg[1].get_data_arr(arr[0]);
    mem_wb_reg[0].get_data_arr(arr[1]);
    if_id_reg[2].get_data_arr(arr[2]); //___DO_ add extra old_pc pipeline regs.
    if_id_reg[2].get_data_arr(arr[3]);

    //mux4
    multiplexers[4].clock_step(arr);

    //mem_to_reg/link
    bool ctrl[2] = { mem_wb_reg[2].get_data(2), mem_wb_reg[2].get_data(0) };
    multiplexers[4].get_output(ctrl, buffers[0]);

    //get destination register
    if(mem_wb_reg[2].get_data(2) == false){
        for (int i = 0; i < 5; i++){
            write_reg_bin[i] = mem_wb_reg[2].get_data(27 + i); 
        } 
        write_reg = bin_to_int(write_reg_bin, 5);
    }

    //write back to register file
    registers.clk_step(
        0,
        0,
        write_reg,
        buffers[0],
        mem_wb_reg[2].get_data(1)
    );
}

void Cpu::load_instructions(bool arr[][32], int length){
    ram.load_instructions(arr, length);
}

void Cpu::print_registers(){
    std::cout <<"________________________________________"<<std::endl;
    registers.print();
    std::cout <<"________________________________________"<<std::endl;
}

void Cpu::print_pipeline_registers(){
    std::cout <<"________________________________________"<<std::endl;
    std::cout << std::endl << " if_id_regs::"<< std::endl;
    for (int i = 0; i < 3; i++){
        if_id_reg[i].print();
    }

    std::cout << std::endl << " id_ex_regs::"<< std::endl;
    for (int i = 0; i < 5; i++){
        id_ex_reg[i].print();
    }

    std::cout << std::endl << "   alu regs::"<< std::endl;
    alu_a_reg.print();
    alu_b_reg.print();

    std::cout << std::endl << "ex_mem_regs::"<< std::endl;
    for (int i = 0; i < 4; i++){
        ex_mem_reg[i].print();
    }

    std::cout << std::endl << "mem_wb_regs::"<< std::endl;
    for (int i = 0; i < 3; i++){
        mem_wb_reg[i].print();
    }

    std::cout << std::endl;

    pc.print();
    std::cout <<"________________________________________"<<std::endl;
}

void Cpu::print_ram(int num){
    ram.print(num);
}

void Cpu::print_data(){
    ram.print_data();
}

void Cpu::print_instructions(){
    ram.print_instructions();
}

void Cpu::print_control(){
    control.print();
}
