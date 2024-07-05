#include "register.h"

typedef Reg_32 register_array[32];

class Register_File {
    public:
        Register_File();
        void get_rs(bool arr[32]);
        void get_rt(bool arr[32]);
        void clk_step(int _rs, int _rt, int _rd, bool _wb_data[32], bool _reg_wrt);
        void print();

    private:

        register_array registers = {};

        //inputs
        int rs;
        int rt;
        int rd;
        bool wb_data[32] = {};
        bool reg_write;

        //outputs
        bool rs_out[32] = {};
        bool rt_out[32] = {};
        
        void set_register(int index, bool data[], int size);
        void get_register(int index, bool arr[32]);

};

Register_File::Register_File(){
    rs = 0;
    rt = 0;
    rd = 0;
    reg_write = false;

    registers[0].set_name("$zero");
    registers[1].set_name("$at");
    registers[2].set_name("$v0");
    registers[3].set_name("$v1");
    registers[4].set_name("$a0");
    registers[5].set_name("$a1");
    registers[6].set_name("$a2");
    registers[7].set_name("$a3");
    registers[8].set_name("$t0");
    registers[9].set_name("$t1");
    registers[10].set_name("$t2");
    registers[11].set_name("$t3");
    registers[12].set_name("$t4");
    registers[13].set_name("$t5");
    registers[14].set_name("$t6");
    registers[15].set_name("$t7");
    registers[16].set_name("$s0");
    registers[17].set_name("$s1");
    registers[18].set_name("$s2");
    registers[19].set_name("$s3");
    registers[20].set_name("$s4");
    registers[21].set_name("$s5");
    registers[22].set_name("$s6");
    registers[23].set_name("$s7");
    registers[24].set_name("$t8");
    registers[25].set_name("$t9");
    registers[26].set_name("$k0");
    registers[27].set_name("$k1");
    registers[28].set_name("$gp");
    registers[29].set_name("$sp");
    registers[30].set_name("$fp");
    registers[31].set_name("$ra");
}

void Register_File::set_register(int index, bool data[], int size){
    if (index > 31) {index = 31;}
    if (index < 0) {index = 0;}
    
    registers[index].fill_arr_lower(data, size);
}

void Register_File::get_register(int index, bool arr[32]){
    for (int i = 0; i < 32; ++i) {
        arr[i] = registers[index].get_data(i);
    }
}

void Register_File::get_rs(bool arr[32]){
    for (int i = 0; i < 32; ++i) {
        arr[i] = rs_out[i];
    }
}

void Register_File::get_rt(bool arr[32]){
    for (int i = 0; i < 32; ++i) {
        arr[i] = rt_out[i];
    }
}

void Register_File::clk_step(int _rs, int _rt, int _rd, bool _wb_data[32], bool _reg_wrt){

    //handle inputs
    rs = _rs;
    rt = _rt;
    rd = _rd;
    
    //wrt back
    if(reg_write){
        for (int i = 0; i < 32; ++i) {
            wb_data[i] = _wb_data[i];
        }
        set_register(rd, wb_data, 32);
    }
    else{
        //handle outputs
        get_register(rs, rs_out);
        get_register(rt, rt_out);
    }

}

void Register_File::print(){
    
    std::cout << "registers::" << std::endl;

    for(int i = 0; i < 32; i++){
        registers[i].print();
    }
    
}
