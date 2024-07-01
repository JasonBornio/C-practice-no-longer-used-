#include <vector>
#include <math.h>
#include <iostream>

int g_dim = 32;

int bin_to_int(bool bin[], int size){
    if (size > g_dim) {size = g_dim;}

    int value = 0;
    
    for(int i = 0; i < size; i++){
        if(bin[(size-1) - i])
            if(i == 31){
                value -= pow(2, i);
            }
            else{
                value += pow(2, i);
            }
    } 

    return value;
}

void int_to_bin(int num, bool arr[], int size){
    if (size > g_dim) {size = g_dim;}

    for (int i = 0; i < size; ++i) {
        arr[size - 1 - i] = (num >> i) & 1;
    }
    
}

void print_bin(bool bin[], int size){
    if (size > g_dim) {size = g_dim;}
    
    std::cout <<"binary: ";

    for (int i = 0; i < size; i++){
        std::cout << int(bin[i]);
    }

    std::cout << std::endl;
}
