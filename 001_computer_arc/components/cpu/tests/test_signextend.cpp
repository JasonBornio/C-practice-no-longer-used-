#include "../signextend.h"
#include "../utilities.h"

int main(){
    
    Sign_Extend sign_extend;
    bool output[32];

    bool byte[8];
    int_to_bin(187, byte, 8);
    sign_extend.extend_byte(byte);
    sign_extend.get_output(output);
    print_bin(output, 32);

    int_to_bin(77, byte, 8);
    sign_extend.extend_byte(byte);
    sign_extend.get_output(output);
    print_bin(output, 32);

    bool half[16];
    int_to_bin(40001, half, 16);
    sign_extend.extend_half(half);
    sign_extend.get_output(output);
    print_bin(output, 32);

    int_to_bin(25000, half, 16);
    sign_extend.extend_half(half);
    sign_extend.get_output(output);
    print_bin(output, 32);

}