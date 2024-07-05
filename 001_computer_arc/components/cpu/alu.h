#include "programcounter.h"

class Arithmetic_Logic_Unit {
    public:
        Arithmetic_Logic_Unit();

        void clock_step(Reg_32 A, Reg_32 B, bool control[6], bool opcode);
        void get_output(bool arr[32]);
        bool zero();

    private:
        bool output[32];
        bool _zero;

};

Arithmetic_Logic_Unit::Arithmetic_Logic_Unit(){

}

void Arithmetic_Logic_Unit::clock_step(Reg_32 A, Reg_32 B, bool control[6], bool opcode){

}

void Arithmetic_Logic_Unit::get_output(bool arr[32]){
    for (int i = 0; i < 32; i++){
        arr[i] = output[i];
    }
}

bool Arithmetic_Logic_Unit::zero(){
    return _zero;
}
