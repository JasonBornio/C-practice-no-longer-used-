#include "../control.h"

int main(){
    Control ctrl;

    bool opcode[6];
    bool funct[6];
    bool signals[19];

    int_to_bin(0, opcode, 6);
    int_to_bin(0, funct, 6);

    ctrl.set_signals(opcode, funct);
    ctrl.get_output(signals);

    std::cout<<" ADD:________________"<<std::endl;
    ctrl.print();
    ctrl.print_desc();

    int_to_bin(8, opcode, 6);
    int_to_bin(3142, funct, 6);

    ctrl.set_signals(opcode, funct);
    ctrl.get_output(signals);

    std::cout<<"ADDI:________________"<<std::endl;
    ctrl.print();
    ctrl.print_desc();

    int_to_bin(2, opcode, 6);
    int_to_bin(9796, funct, 6);

    ctrl.set_signals(opcode, funct);
    ctrl.get_output(signals);

    std::cout<<"JUMP:________________"<<std::endl;
    ctrl.print();
    ctrl.print_desc();

    int_to_bin(0, opcode, 6);
    int_to_bin(8, funct, 6);

    ctrl.set_signals(opcode, funct);
    ctrl.get_output(signals);

    std::cout<<"  JR:________________"<<std::endl;
    ctrl.print();
    ctrl.print_desc();

    int_to_bin(43, opcode, 6);
    int_to_bin(42525, funct, 6);

    ctrl.set_signals(opcode, funct);
    ctrl.get_output(signals);

    std::cout<<"  SW:________________"<<std::endl;
    ctrl.print();
    ctrl.print_desc();


    int_to_bin(35, opcode, 6);
    int_to_bin(2500, funct, 6);

    ctrl.set_signals(opcode, funct);
    ctrl.get_output(signals);

    std::cout<<"  LW:________________"<<std::endl;
    ctrl.print();
    ctrl.print_desc();

    int_to_bin(4, opcode, 6);
    int_to_bin(110, funct, 6);

    ctrl.set_signals(opcode, funct);
    ctrl.get_output(signals);

    std::cout<<" BEQ:________________"<<std::endl;
    ctrl.print();
    ctrl.print_desc();


} 
