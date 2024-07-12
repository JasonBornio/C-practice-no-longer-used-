#include "../subtractor.h"
#include <stdio.h>

int main(){

    bool arr[32];

    Reg_32 reg1;
    Reg_32 reg2;

    reg1.set_name("reg1");
    reg2.set_name("reg2");

    int_to_bin(500, arr, 32);
    reg1.fill_arr_lower(arr, 32);

    int_to_bin(130, arr, 32);
    reg2.fill_arr_lower(arr, 32);

    reg1.print();
    reg2.print();


    Reg_32 result;
    Subtractor_32 subber;

    std::cout<< "reg1 - reg2:" << std::endl;

    result = subber.sub(reg1, reg2);
    result.set_name("result");
    result.print();

    std::cout<< "sub 1 to reg1 :" << std::endl;

    result = subber.sub_one(reg1);
    result.set_name("result");
    result.print();

    std::cout<< "sub 32 to reg1:" << std::endl;

    result = subber.sub_int(reg1, 32);
    result.set_name("result");
    result.print();
} 
