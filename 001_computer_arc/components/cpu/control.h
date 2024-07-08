#include "mux.h"

class Control {
    public:
        Control();

        void get_output(bool array[19]);
        void set_signals(bool opcode[6], bool func[6]);

        void print();

    private:

        bool alu_control[4] = {true, true, true, true };

        bool alu_src;
        bool reg_dst;
        bool reg_wrt;
        bool mem_read;
        bool mem_wrt;
        bool mem_to_reg;
        bool branch;
        bool set_reg31;

        bool jump;

        bool signals[19] = {};
        void reset_signals();

};

Control::Control(){
    this->alu_src = false;
    this->reg_dst = false;
    this->reg_wrt = false;
    this->mem_read = false;
    this->mem_wrt = false;
    this->mem_to_reg = false;
    this->branch = false;
    this->set_reg31 = false;

    this->jump = false;
}

void Control::get_output(bool array[19]){
    for(int i = 0; i < 19; i++){
        array[i] = this->signals[i];
    }
}

void Control::set_signals(bool opcode[6], bool func[6]){

    reset_signals();

    bool r_type = true;

    for (int i = 0; i < 6; i++){
        if(opcode[i]) r_type = false;
    }

    if(r_type){
        if (func[0]){
            //alu inst
            for(int i = 0; i < 4; i++){
                this->alu_control[i] = func[i+2];
            }
            this->reg_wrt = true;
        }
        else if(func[2]){
            //jump reg
            this->jump = true;
            if(func[5]) {this->reg_wrt = true; this->set_reg31 = true;}
        }
        else if(func[2] && func[3]){
            //other
        }
        else{
            //shift
            this->reg_wrt = true;
        }

    }
    else{
        //this->reg_dst = true;
        if(opcode[0]){
            //mem access imm
            if(opcode[2]){
                //store
                this->mem_wrt = true;
                this->alu_src = true;

            }
            else{
                //load
                this->mem_read = true;
                this->mem_to_reg = true;
                this->reg_wrt = true;
                this->reg_dst = true;
                this->alu_src = true;
            }
        }
        else if(opcode[1]){
            //other
        }
        else if(opcode[2]){
            //alu imm
            //using alu
            this->alu_control[3] = false;
            this->alu_src = true;
            this->reg_dst = true;
            this->reg_wrt = true;
        }
        else if(!opcode[3] && opcode[4]){
            this->jump = true;
        }
        else{
            //using alu
            //branch imm
            this->branch = true;
            this->alu_control[3] = false;
            
        }
    }

    for (int i = 0; i < 4; i++){
       this->signals[i] = this->alu_control[i];
       this->signals[i+4] = opcode[i];
    }

    this->signals[8] = opcode[4];
    this->signals[9] = opcode[5];
    this->signals[10] = this->alu_src;
    this->signals[11] = this->reg_dst;
    this->signals[12] = this->branch;
    this->signals[13] = this->mem_read;
    this->signals[14] = this->mem_wrt;
    this->signals[15] = this->mem_to_reg;
    this->signals[16] = this->reg_wrt;
    this->signals[17] = this->jump;
    this->signals[18] = this->set_reg31;
    
}

void Control::reset_signals(){

    for(int i = 0; i < 4; i++){
        this->alu_control[i] = true;
    }

    this->alu_src = false;
    this->reg_dst = false;
    this->reg_wrt = false;
    this->mem_read = false;
    this->mem_wrt = false;
    this->mem_to_reg = false;
    this->branch = false;

    this->jump = false;
}

void Control::print(){
    std::cout << "  control: { ";

    for (int i = 0; i < 19; i++){
        std::cout << int(this->signals[i]);
    }

    std::cout << " }"<< std::endl;
}
