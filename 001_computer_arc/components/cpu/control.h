#include "mux.h"

class Control {
    public:
        Control();

        void get_output(bool array[22]);
        void set_signals(bool opcode[6], bool func[6]);

        void print();
        void print_desc();

    private:

        bool alu_control[6] = {true, true, true, true, true, true};

        bool alu_src;
        bool reg_dst;
        bool reg_wrt;
        bool mem_read;
        bool mem_wrt;
        bool mem_to_reg;
        bool branch;
        bool link;

        bool jump[2];

        bool signals[22] = {};
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
    this->link = false;

    this->jump[0] = false;
    this->jump[1] = false;
}

void Control::get_output(bool array[22]){
    for(int i = 0; i < 22; i++){
        array[i] = this->signals[i];
    }
}

void Control::set_signals(bool opcode[6], bool func[6]){

    reset_signals();

    bool r_type = true;

    for (int i = 0; i < 6; i++){
        if(opcode[i]) r_type = false;
    }

    int code = bin_to_int(func ,6);

    if(r_type){
        if (func[0] || code < 8){
            //alu inst
            for(int i = 0; i < 6; i++){
                this->alu_control[i] = func[i];
            }
            this->reg_wrt = true;
        }
        else if(func[2]){
            //jump reg
            this->reg_wrt = true;
            this->jump[0] = true;
            this->jump[1] = true;
            if(func[5]) this->link = true;
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
            this->alu_control[5] = false;
            this->alu_src = true;
            this->reg_dst = true;
            this->reg_wrt = true;
        }
        else if(!opcode[3] && opcode[4]){
            //jump
            if (opcode[5]) {this->jump[1] = true; this->link = true; this->reg_wrt = true;}
            else this->jump[0] = true;
        }
        else{
            //using alu
            //branch imm
            this->branch = true;
            this->alu_control[5] = false;
        }
    }

    for (int i = 0; i < 6; i++){
       this->signals[i] = this->alu_control[i];
       this->signals[i+6] = opcode[i];
    }

    this->signals[12] = this->alu_src;
    this->signals[13] = this->reg_dst;
    this->signals[14] = this->branch;
    this->signals[15] = this->mem_read;
    this->signals[16] = this->mem_wrt;
    this->signals[17] = this->mem_to_reg;
    this->signals[18] = this->reg_wrt;
    this->signals[19] = this->jump[0];
    this->signals[20] = this->jump[1];
    this->signals[21] = this->link;
    
}

void Control::reset_signals(){

    for(int i = 0; i < 6; i++){
        this->alu_control[i] = true;
    }

    this->alu_src = false;
    this->reg_dst = false;
    this->reg_wrt = false;
    this->mem_read = false;
    this->mem_wrt = false;
    this->mem_to_reg = false;
    this->branch = false;

    this->jump[0] = false;
    this->jump[1] = false;

    this->link = false;
}

void Control::print(){
    std::cout << "  control: { ";

    for (int i = 0; i < 22; i++){
        std::cout << int(this->signals[i]);
    }

    std::cout << " }"<< std::endl;
}

void Control::print_desc(){
    std::cout << "  control: { " << std::endl;

    std::cout << "   alu_ctrl: {";
    for (int i = 0; i < 6; i++){
        std::cout << int(this->signals[i]);
    }
    std::cout << "}"<< std::endl;

    std::cout << "    op_code: {";
    for (int i = 0; i < 6; i++){
        std::cout << int(this->signals[i + 6]);
    }
    std::cout << "}"<< std::endl;

    std::cout << "    alu_src:  "<< this->signals[12] << std::endl;
    std::cout << "    reg_dst:  "<< this->signals[13] << std::endl;
    std::cout << "     branch:  "<< this->signals[14] << std::endl;
    std::cout << "   mem_read:  "<< this->signals[15] << std::endl;
    std::cout << "    mem_wrt:  "<< this->signals[16] << std::endl;
    std::cout << "  memto_reg:  "<< this->signals[17] << std::endl;
    std::cout << "    reg_wrt:  "<< this->signals[18] << std::endl;
    std::cout << "    jump[0]:  "<< this->signals[19] << std::endl;
    std::cout << "    jump[1]:  "<< this->signals[20] << std::endl;
    std::cout << "       link:  "<< this->signals[21] << std::endl;

    std::cout << "  }"<< std::endl;
}
