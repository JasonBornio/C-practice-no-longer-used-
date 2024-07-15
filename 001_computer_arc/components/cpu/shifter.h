#include "cpu/alu.h"
#include "cpu/signextend.h"

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
        Reg_32 alu_a_reg;
        Reg_32 alu_b_reg;
        Reg_32 alu_out_reg;

        //msb of last 3 regs are control signals
        //first 5 lsb of last 3 regs are rs rt rd.
        Reg_32 if_id_reg[2] = {};
        Reg_32 id_ex_reg[5] = {};
        Reg_32 ex_mem_reg[4] = {};
        Reg_32 mem_wb_reg[3] = {};

        
        Random_Access_Memory ram;
        Register_File registers;
        Program_Counter pc;
        Arithmetic_Logic_Unit alu;
        Control control;
        Multiplexer_2 multiplexers[5];
        Sign_Extend sign_extend;
        Adder_32 adder;
        Shifter shift_left;

        bool pc_src;

        bool buffer[32];

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
    alu_out_reg.set_name("$alu_out");
    
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
    }
}

void Cpu::execute_instructions(){
    while (pc.get_pc() <  ram.get_top_inst_pointer() + 4){
        clock_step();
    }
}

void Cpu::instruction_fetch(){

    pc.get_pc(buffer);

    bool arr_1[4][32];
    bool arr_2[4][32];

    for(int i = 0; i < 32; i++){
        arr_1[0][i] = buffer[i];
        arr_1[1][i] = ex_mem_reg[0].get_data(i);
    }

    bool ctrl[2] = { false, pc_src };

    multiplexers[0].clock_step(arr_1);
    multiplexers[0].get_output(ctrl, buffer);

    bool arr[32];
    id_ex_reg[3].get_data_arr(arr);

    //shifter
    shift_left.shift(arr);
    shift_left.get_output(arr);
    id_ex_reg[3].fill_arr_lower(arr, 32);

    for (int i = 0; i < 32; i ++){
        arr_2[0][i] = buffer[i];
        arr_2[1][i] = id_ex_reg[3].get_data(i);
    }

    ctrl[1] = ex_mem_reg[3].get_data(5);
    
    multiplexers[1].clock_step(arr_2);
    multiplexers[1].get_output(ctrl, buffer);

    //shift it

    pc.jump(buffer);

    ram.inst_clk_step(buffer);
    ram.get_data_out(buffer);
    if_id_reg[1].fill_arr_lower(buffer, 32);
    
    pc.increment();
    pc.get_pc(buffer);
    if_id_reg[0].fill_arr_lower(buffer, 32);
}

void Cpu::instruction_decode(){

    //pass pc
    id_ex_reg[0].copy(if_id_reg[0]);
        
    //decode inst
    bool opcode[6];
    bool func[6];
    bool jump = true;

    for (int i = 0; i < 6; i++){
        opcode[i] = if_id_reg[1].get_data(i);
        func[i] = if_id_reg[1].get_data(i+26);
        if(i < 4 && opcode[i]){
            jump = false;
        }
    }

    //get inst
    if_id_reg[1].get_data_arr(buffer);
    int opcode_int = bin_to_int(opcode, 6);

    if(jump && opcode[4]){
        //std::cout<<"JUMP"<<std::endl;
        //jump
        jump_inst instruction = create_jump_inst(buffer);
        id_ex_reg[3].fill_arr_lower(instruction.target, 26);
    }
    else if (opcode_int){
        //imm
        //std::cout<<"IMMM"<<std::endl;
        immediate_inst instruction = create_immediate_inst(buffer);

        //mem_wb_reg[1].get_data_arr(buffer);

        registers.clk_step(
            instruction.int_rs,
            instruction.int_rt,
            31,
            buffer,
            false
        );

        //get registers
        registers.get_rs(buffer);
        id_ex_reg[1].fill_arr_lower(buffer, 32);
        registers.get_rt(buffer);
        id_ex_reg[2].fill_arr_lower(buffer, 32);

        sign_extend.extend_half(instruction.imm);
        sign_extend.get_output(buffer);
        
        id_ex_reg[3].fill_arr_lower(buffer, 32);
        id_ex_reg[4].fill_arr_lower(instruction.rt, 5);

    }
    else{
        //rtype:
        r_type_inst instruction = create_r_type_inst(buffer);

        //mem_wb_reg[1].get_data_arr(buffer);

        registers.clk_step(
            instruction.int_rs,
            instruction.int_rt,
            31,
            buffer,
            false
        );

        registers.get_rt(buffer);
        id_ex_reg[2].fill_arr_lower(buffer, 32);
        //get registers
        registers.get_rs(buffer);
        id_ex_reg[1].fill_arr_lower(buffer, 32);

        if(!func[0] && func[2]){
            std::cout<<"JUMP"<<std::endl;
            //jump
            id_ex_reg[3].fill_arr_lower(buffer, 32);
            pc.get_pc(buffer);
            id_ex_reg[2].fill_arr_lower(buffer, 32);
        }
        else{
            id_ex_reg[3].fill_arr_lower(instruction.shamt, 5);
        }

        id_ex_reg[4].fill_arr_lower(instruction.rt, 5);
        id_ex_reg[4].fill_arr_lower(instruction.rd, 5, 5);

    }

    //control signals
    bool signals[21];
    control.set_signals(opcode, func);
    control.get_output(signals);
    id_ex_reg[4].fill_arr_upper(signals, 21);

    // std::cout<<"opfunc:: ";
    // print_bin(opcode, 6);
    // print_bin(func, 6);
    // std::cout<<"signal:: ";
    // print_bin(signals, 19);

}

void Cpu::execute(){

    //update pc
    //NEED SHIFTER HERE !!!
    id_ex_reg[3].get_data_arr(buffer);
    shift_left.shift(buffer);
    shift_left.get_output(buffer);

    ex_mem_reg[0] = adder.add_int(id_ex_reg[0], bin_to_int(buffer, 32));
    ex_mem_reg[0].set_name("$p_pc");

    //alu inputs
    bool arr_1[4][32] = {};
    bool arr_2[4][32] = {};

    id_ex_reg[2].get_data_arr(arr_1[0]);
    id_ex_reg[3].get_data_arr(arr_1[1]);
    multiplexers[2].clock_step(arr_1);

    //alu_src
    bool ctrl[2] = {false, id_ex_reg[4].get_data(12)};
    multiplexers[2].get_output(ctrl, buffer);

    alu_b_reg.fill_arr_lower(buffer, 32);
    id_ex_reg[1].get_data_arr(buffer);
    alu_a_reg.fill_arr_lower(buffer, 32);

    bool alu_ctrl[6];
    bool alu_op[6];
    bool alu_shamt[5];

    for (int i = 0; i < 6; i++){
        alu_ctrl[i] = id_ex_reg[4].get_data(i);
        alu_op[i] = id_ex_reg[4].get_data(i+6);
        if(i < 5)
            alu_shamt[i] = id_ex_reg[3].get_data(i+27);
    }

    // std::cout<<"alu_ctrl:: ";
    // print_bin(alu_ctrl, 4);
    // std::cout<<"alu_op :: ";
    // print_bin(alu_op, 6);

    //alu func
    alu.clock_step(alu_a_reg, alu_b_reg, alu_ctrl, alu_op, alu_shamt);
    alu_out_reg = alu.get_output();
    alu_out_reg.set_name("$alu_out");
    ex_mem_reg[1].copy(alu_out_reg);

    //data reg
    ex_mem_reg[2].copy(id_ex_reg[2]);

    //write reg
    
    for (int i = 0; i < 5; i++){
        arr_2[0][27+i] = id_ex_reg[4].get_data(22+i);
        arr_2[1][27+i] = id_ex_reg[4].get_data(27+i);
    }

    //reg_dst
    multiplexers[3].clock_step(arr_2);
    ctrl[1] = id_ex_reg[4].get_data(13);

    multiplexers[3].get_output(ctrl, buffer);
    ex_mem_reg[3].fill_arr_lower(buffer, 32);

    //control signals
    bool signals[11] = {
        id_ex_reg[4].get_data(14),
        id_ex_reg[4].get_data(15),
        id_ex_reg[4].get_data(16),
        id_ex_reg[4].get_data(17),
        id_ex_reg[4].get_data(18),
        id_ex_reg[4].get_data(19),
        alu.zero(),
        id_ex_reg[4].get_data(6),
        id_ex_reg[4].get_data(7),
        id_ex_reg[4].get_data(8),
        id_ex_reg[4].get_data(9)
    };
    ex_mem_reg[3].fill_arr_upper(signals, 11);
}
 
void Cpu::memory_acess(){

    //memory access
    bool data_reg[32];
    bool ram_ctrl[4];
    ex_mem_reg[1].get_data_arr(buffer);
    ex_mem_reg[2].get_data_arr(data_reg);

    for(int i = 0; i<4; i++){
        ram_ctrl[i] = ex_mem_reg[3].get_data(7+i);
    }

    ram.data_clk_step(
        buffer, 
        data_reg, 
        ex_mem_reg[3].get_data(2),
        ex_mem_reg[3].get_data(1),
        ram_ctrl
    );
    
    ram.get_data_out(buffer);

    //pipeline register
    mem_wb_reg[0].fill_arr_lower(buffer, 32);
    mem_wb_reg[1].copy(ex_mem_reg[1]);
    mem_wb_reg[2].copy(ex_mem_reg[3]);

    //control signals
    bool signals[2] = {
        ex_mem_reg[3].get_data(3),
        ex_mem_reg[3].get_data(4)
    };
    mem_wb_reg[2].fill_arr_upper(signals, 2);

    //and gate
    pc_src = (ex_mem_reg[3].get_data(0)) && ex_mem_reg[3].get_data(6);

}

void Cpu::write_back(){
    bool arr[4][32];
    bool write_reg_bin[5];
    
    mem_wb_reg[1].get_data_arr(arr[0]);
    mem_wb_reg[0].get_data_arr(arr[1]);

    for (int i = 0; i < 5; i++){
        write_reg_bin[i] = mem_wb_reg[2].get_data(27 + i); 
    } 

    multiplexers[4].clock_step(arr);

    bool ctrl[2] = {false, mem_wb_reg[2].get_data(0)};
    multiplexers[4].get_output(ctrl, buffer);

    int write_reg = bin_to_int(write_reg_bin, 5);

    // print_bin(buffer, 32);
    // print_bin(write_reg_bin, 5);
    // std::cout << mem_wb_reg[2].get_data(1)<< ", "<<write_reg<<std::endl;

    registers.clk_step(
        0,
        0,
        write_reg,
        buffer,
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
    for (int i = 0; i < 2; i++){
        if_id_reg[i].print();
    }

    std::cout << std::endl << " id_ex_regs::"<< std::endl;
    for (int i = 0; i < 5; i++){
        id_ex_reg[i].print();
    }

    std::cout << std::endl << "   alu regs::"<< std::endl;

    alu_a_reg.print();
    alu_b_reg.print();
    alu_out_reg.print();

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
