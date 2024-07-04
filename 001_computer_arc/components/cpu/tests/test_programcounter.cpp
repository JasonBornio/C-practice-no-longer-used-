#include "../programcounter.h"
#include <stdio.h>

int main(){
    Programcounter pc;

    pc.print();

    pc.increment();
    pc.print();

    pc.branch(50);
    pc.print();

    pc.jump(120);
    pc.print();

    pc.branch(400);
    pc.print();

    pc.jump(20);
    pc.print();

}