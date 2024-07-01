#include "../register_file.h"

int main(){

    Register_File reg_file;

    bool arr[8] = {true, false, true, false, true, false, true, true};
    bool arr2[8] = {true, true, true, true, true, false, true, false};

    bool arr_data[32];

    Reg_32 reg;
    reg.fill_arr_lower(arr, 8);
    reg.get_data_arr(arr_data);

    reg_file.clk_step(1, 2, 1, arr_data, true);

    reg.fill_arr_lower(arr2, 8);
    reg.get_data_arr(arr_data);
    
    reg_file.clk_step(1, 2, 3, arr_data, true);

    reg_file.get_rs(arr_data);

    reg.fill_arr_lower(arr_data, 32);
    reg.set_name("data");
    reg.print();

    reg_file.print();
}
