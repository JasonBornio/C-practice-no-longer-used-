#include "../mux.h"

int main(){

    bool arr[4][32] = {};

    int_to_bin(255, arr[0], 32);
    int_to_bin(1200000000, arr[1], 32);
    int_to_bin(1024, arr[2], 32);
    int_to_bin(6553633, arr[3], 32);

    bool control[4][2] = {
        { false, false },
        { false, true },
        { true, false },
        { true, true }
    };

    Multiplexer_2 mux;

    bool output_arr[32];

    mux.clock_step(arr);
    mux.get_output(control[3], output_arr);
    mux.print();

    mux.clock_step(arr);
    mux.get_output(control[2], output_arr);
    mux.print();

    mux.clock_step(arr);
    mux.get_output(control[1], output_arr);
    mux.print();

    mux.clock_step(arr);
    mux.get_output(control[0], output_arr);
    mux.print();


} 
