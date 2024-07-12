#include "register_file.h"

class Subtractor_32 {
    public:

    Subtractor_32();

    Reg_32 sub(Reg_32& r1, Reg_32& r2);
    Reg_32 sub_one(Reg_32& r1);
    Reg_32 sub_int(Reg_32& r1, int num);

    bool underflow_flag;

};

Subtractor_32::Subtractor_32(){
    underflow_flag = false;
}

Reg_32 Subtractor_32::sub(Reg_32& r1, Reg_32& r2){
    underflow_flag = false;

    bool differnece = false;
    bool b_out = false;
    bool b_in = false;
    bool a = false;
    bool b = false;

    bool result[32] = {};

    for(int i = 31; i > 0; i--){

        a = r1.get_data(i);
        b = r2.get_data(i);

        differnece = (a ^ b) ^ b_in;
        b_out = (!(a ^ b) && (b_in)) || (!a && b);

        b_in = b_out;

        result[i] = differnece;
    }

    if(b_in){
        underflow_flag = true;
    }

    Reg_32 output;
    output.fill_arr_lower(result, 32);

    return output;
}

Reg_32 Subtractor_32::sub_one(Reg_32& r1){

    Reg_32 r2;
    r2.fill_ones_lower(1);

    return sub(r1, r2);
}

Reg_32 Subtractor_32::sub_int(Reg_32& r1, int num){

    Reg_32 r2;
    bool arr[32] = {};

    int_to_bin(num, arr, 32);
    r2.fill_arr_lower(arr, 32);

    return sub(r1, r2);
}