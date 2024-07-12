#include "../adder.h"
#include <stdio.h>

int main(){

    bool arr[8] = {true, false, true, false, true, false, true, false};

    Reg_32 reg1;
    Reg_32 reg2;

    reg1.set_name("reg1");
    reg2.set_name("reg2");

    reg1.fill_arr_lower(arr, 8);
    reg2.fill_ones_lower(8);

    reg1.print();
    reg2.print();


    Reg_32 result;
    Adder_32 adder;

    std::cout<< "reg1 + reg2:" << std::endl;

    result = adder.add(reg1, reg2);
    result.set_name("result");
    result.print();

    std::cout<< "add 1 to reg1 :" << std::endl;

    result = adder.add_one(reg1);
    result.set_name("result");
    result.print();

    std::cout<< "add -32 to reg1:" << std::endl;

    bool neg_arr[32];
    int_to_bin(-22, neg_arr, 32);
    print_bin(neg_arr, 32);

    result = adder.add_int(reg1, -22);
    std::cout << "overflow: "<< adder.overflow_flag<<std::endl;
    result.set_name("result");
    result.print();
} 
