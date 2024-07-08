#include "../register.h"

int main(){

    bool arr[8] = {true, false, true, false, true, false, true, false};

    Reg_32 reg1;
    Reg_32 reg2;

    reg1.set_name("reg1");
    reg2.set_name("reg2");

    reg1.fill_arr_lower(arr, 8);
    reg1.fill_arr_lower(arr, 8, 8);
    std::cout << "data at index 30: " << reg1.get_data(30) << std::endl;

    reg2.fill_arr_upper(arr, 8);

    reg1.print();
    reg2.print();

    Reg_32 result;

    result = reg1 | reg2;

    result.set_name("or");
    result.print();

    result = reg1 & reg2;

    result.set_name("and");
    result.print();

    reg1.clear();
    reg1.print();

    reg1.fill_ones_lower(8);
    reg1.print();

    reg1.fill_ones_upper(16);
    reg1.print();

    result = reg1 & reg2;

    result.set_name("and");
    result.print();

    result = reg1 ^ reg2;

    result.set_name("xor");
    result.print();

    reg1 = ~reg1;
    reg1.print();

    reg2.print();
    reg2.copy(reg1);
    reg2.print();
}
