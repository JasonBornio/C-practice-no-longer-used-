#include "../shifter.h"

int main(){
    Shifter shift_left;

    bool arr[32];
    bool shamt[5];
    int_to_bin(65535, arr, 32);
    int_to_bin(8, shamt, 5);

    Reg_32 result;
    result.set_name("$result");

    shift_left.shift(arr);
    shift_left.print();

    shift_left.clock_step(arr, shamt);
    shift_left.get_output(arr);
    
    result.fill_arr_lower(arr, 32);
    result.print();

} 
