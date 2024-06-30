#include "../utilities.h"
#include <stdio.h>   

int main(){

    bool arr[4] = { false, true, false, true };
    int num = bin_to_int(arr, 4);

    printf ("bin to int: %d\n", num);

    num = 14;

    print_bin(arr, 4);
    int_to_bin(num, arr, 4);
    print_bin(arr, 4);

}
