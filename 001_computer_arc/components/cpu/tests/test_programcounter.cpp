#include "../programcounter.h"
#include <stdio.h>

int main(){
    Program_Counter pc;
    bool arr[32];

    pc.print();

    pc.increment();
    pc.print();

    int_to_bin(50, arr, 32);
    pc.branch(arr);
    pc.print();

    int_to_bin(120, arr, 32);
    pc.jump(arr);
    pc.print();
        
    int_to_bin(400, arr, 32);
    pc.branch(arr);
    pc.print();
    
    int_to_bin(20, arr, 32);
    pc.jump(arr);
    pc.print();

}
