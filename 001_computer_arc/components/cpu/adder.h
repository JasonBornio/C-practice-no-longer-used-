#include "register.h"

class Adder_32 {
    public:

    Adder_32();

    Reg_32 add(Reg_32& r1, Reg_32& r2);
    Reg_32 add_one(Reg_32& r1);
    Reg_32 add_int(Reg_32& r1, int num);

    bool overflow_flag;

};

Adder_32::Adder_32(){
    overflow_flag = false;
}

Reg_32 Adder_32::add(Reg_32& r1, Reg_32& r2){
    overflow_flag = false;

    bool sum = false;
    bool c_out = false;
    bool c_in = false;
    bool a = false;
    bool b = false;

    bool result[32] = {};

    for(int i = constants::g_dim - 1; i > 0; i--){

        a = r1.get_data(i);
        b = r2.get_data(i);

        sum = (a ^ b) ^ c_in;
        c_out = ((a ^ b) && (c_in)) || (a && b);

        c_in = c_out;

        result[i] = sum;
    }

    if(c_in){
        overflow_flag = true;
    }

    Reg_32 output;
    output.fill_arr_lower(result, constants::g_dim);

    return output;
}

Reg_32 Adder_32::add_one(Reg_32& r1){

    Reg_32 r2;
    r2.fill_ones_lower(1);

    return add(r1, r2);
}

Reg_32 Adder_32::add_int(Reg_32& r1, int num){

    Reg_32 r2;
    bool arr[32] = {};

    int_to_bin(num, arr, constants::g_dim);
    r2.fill_arr_lower(arr, constants::g_dim);

    return add(r1, r2);
}
