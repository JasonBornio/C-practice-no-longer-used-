#include "cpu.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

map<string, array<int,3>> instruction_map = {
    {"add",    array<int,3>{0, 0, 32} },
    {"addu",   array<int,3>{0, 0, 33} },
    {"and",    array<int,3>{0, 0, 36} },
    {"nor",    array<int,3>{0, 0, 39} },
    {"or",     array<int,3>{0, 0, 37} },
    {"slt",    array<int,3>{0, 0, 42} },
    {"sltu",   array<int,3>{0, 0, 43} },
    {"sub",    array<int,3>{0, 0, 34} },
    {"subu",   array<int,3>{0, 0, 35} },
    {"xor",    array<int,3>{0, 0, 38} },

    {"addi",   array<int,3>{1, 8, 0}  },
    {"addiu",  array<int,3>{1, 9, 0}  },
    {"andi",   array<int,3>{1, 12, 0} },
    {"lui",    array<int,3>{1, 15, 0} },
    {"ori",    array<int,3>{1, 13, 0} },
    {"slti",   array<int,3>{1, 10, 0} },
    {"sltiu",  array<int,3>{1, 11, 0} },
    {"xori",   array<int,3>{1, 14, 0} },

    {"sll",    array<int,3>{0, 0, 0}  },
    {"sllv",   array<int,3>{0, 0, 4}  },
    {"sra",    array<int,3>{0, 0, 3}  },
    {"srav",   array<int,3>{0, 0, 7}  },
    {"srl",    array<int,3>{0, 0, 2}  },
    {"srlv",   array<int,3>{0, 0, 6}  },

    {"beq",    array<int,3>{1, 4, 0}  },
    {"bgez",   array<int,3>{1, 1, 0}  },
    {"bgtzal", array<int,3>{1, 1, 0}  },
    {"bgtz",   array<int,3>{1, 7, 0}  },
    {"blez",   array<int,3>{1, 6, 0}  },
    {"bltz",   array<int,3>{1, 1, 0}  },
    {"bltzal", array<int,3>{1, 1, 0}  },
    {"bne",    array<int,3>{1, 5, 0}  },
    
    {"j",      array<int,3>{2, 2, 0}  },
    {"jal",    array<int,3>{2, 3, 0}  },
    {"jalr",   array<int,3>{0, 0, 9}  },
    {"jr",     array<int,3>{0, 0, 8}  },

    {"break",  array<int,3>{0, 0, 13} },
    {"mfc0",   array<int,3>{3, 16, 0} },
    {"mtc0",   array<int,3>{3, 16, 0} },
    {"syscal", array<int,3>{0, 0, 12} },

    {"lb",     array<int,3>{1, 32, 0} },
    {"lbu",    array<int,3>{1, 36, 0} },
    {"lh",     array<int,3>{1, 33, 0} },
    {"lhu",    array<int,3>{1, 37, 0} },
    {"lw",     array<int,3>{1, 35, 0} },
    {"sb",     array<int,3>{1, 40, 0} },
    {"sh",     array<int,3>{1, 41, 0} },
    {"sw",     array<int,3>{1, 43, 0} }

};

map<string, int> register_map = {

    {"$zero", 0 },
    {"$at",   1 },
    {"$v0",   2 },
    {"$v1",   3 },
    {"$a0",   4 },
    {"$a1",   5 },
    {"$a2",   6 },
    {"$a3",   7 },
    {"$t0",   8 },
    {"$t1",   9 },
    {"$t2",   10 },
    {"$t3",   11 },
    {"$t4",   12 },
    {"$t5",   13 },
    {"$t6",   14 },
    {"$t7",   15 },
    {"$s0",   16 },
    {"$s1",   17 },
    {"$s2",   18 },
    {"$s3",   19 },
    {"$s4",   20 },
    {"$s5",   21 },
    {"$s6",   22 },
    {"$s7",   23 },
    {"$t8",   24 },
    {"$t9",   25 },
    {"$k0",   26 },
    {"$k1",   27 },
    {"$gp",   28 },
    {"$sp",   29 },
    {"$s8",   30 },
    {"$ra",   31 },

};

map<string, int> address_map = {};

class Assembler{
    public:
        Assembler(Cpu& input_cpu);
        void load_file(string file_name, bool pause_bool);
        void run(int num, bool pause_bool);
        void show_registers(bool pause_bool);
        void show_ram_data(bool pause_bool);
        void show_instructions(bool pause_bool);

    private:
        int address_pointer;
        Cpu cpu;
        vector<string> lines;
        int num_lines;
        int num_insts;
        vector<array<bool, 32>> instructions;
        bool abort;

        void pause();
};

Assembler::Assembler(Cpu& input_cpu){
    cpu = input_cpu;
    abort = false;
}

void Assembler::load_file(string file_name, bool pause_bool){
    string myText;
    ifstream MyReadFile(file_name);

    lines = {};
    num_lines = 0;
    num_insts = 0;
    address_pointer = 64;

    if(MyReadFile.is_open()){
        while (getline(MyReadFile, myText)) {
            // Output the text from the file
            //std::cout << myText<<endl;
            num_lines += 1;
            lines.push_back(myText);
        }
        // Close the file
        MyReadFile.close();
    }
    else std::cout << "ERROR reading file";

    vector<vector<string>> list = {};
    abort = false;

    for (int i = 0; i < num_lines; i++){
        string line = lines[i];
        const char *cstr = line.c_str();

        char temp[7] = {'\0','\0','\0','\0','\0','\0','\0'};
        vector<string> values = {to_string(i+1)};
        int index = 0;
        bool push = false;
        char chr;



        for(int j = 0; j < lines[i].size(); j++){
            chr = cstr[j];
            if(chr == '/' || chr=='\n')
                break;

            push = true;
            //std::cout<<chr;
            if(chr == ' ' || chr == ';'){
                string str(temp); 
                // std::cout<<"str:::"<<str<<endl;
                values.push_back(str);

                temp[0] = '\0';
                temp[1] = '\0';
                temp[2] = '\0';
                temp[3] = '\0';
                temp[4] = '\0';
                temp[5] = '\0';
                temp[6] = '\0';
                
                index = 0;

                if(chr==';') break;

            }
            else{
                temp[index] = chr;
                index +=1;
            }
        }

        if(push) {
            if(chr != ';'){
                cerr << "ERROR: statement missing: ';', line: "<< i+1 <<endl; 
                abort =  true;
                return;
            }
            else{
            list.push_back(values);
            num_insts += 1;
            }
        }

    }
    
    for(int i = 0; i < list.size(); i++){

        string code = list[i][1];
        code.erase(std::remove(code.begin(), code.end(), ','), code.end());
        code.erase(std::remove(code.begin(), code.end(), '('), code.end());
        code.erase(std::remove(code.begin(), code.end(), ')'), code.end());
        code.erase(std::remove(code.begin(), code.end(), ':'), code.end());

        //std::cout<<code << ": ";


        if (instruction_map.find(code) == instruction_map.end()) {
            // not found
            if (address_map.find(code) == address_map.end()) {
                //not found
                address_map.insert({code, address_pointer}); 
            }
            else{
                //found
                cerr << "ERROR: address name: '"<< code << "' used more than once, line: "<< list[i][0] <<endl; 
                abort = true;
                return;
            }
        } 
        address_pointer += 4;        
    }

    address_pointer = 64;
    for(int i = 0; i < list.size(); i++){
        int count = 0;
        int type = 0;
        array<int, 3> inst;
        
        int opcode = 0;
        int rs = 0;
        int rt = 0;
        int rd = 0;
        int shamt = 0;
        int func = 0;
        int target = 0;
        int imm = 0;

        int value;

        bool imm_value = false;

        for (int j = 0; j <list[i].size() - 1; j++){
            string code = list[i][j + 1];
            code.erase(std::remove(code.begin(), code.end(), ','), code.end());
            code.erase(std::remove(code.begin(), code.end(), '('), code.end());
            code.erase(std::remove(code.begin(), code.end(), ')'), code.end());
            code.erase(std::remove(code.begin(), code.end(), ':'), code.end());

            //std::cout<<code << ": ";

            if(count == 0){
                if (instruction_map.find(code) == instruction_map.end()) {
                    // not found
                        value = address_map.at(code);
                } else {
                    // found
                    inst = instruction_map.at(code);
                    type = inst[0];
                    //std::cout<<inst[1]<<"-"<<inst[2]<<"| ";
                    count += 1;
                }
            }else{
                
                if (register_map.find(code) == register_map.end()) {
                    //not found
                    if (address_map.find(code) == address_map.end()) {
                        //std::cout<<code<<"| ";
                        try{
                            value = stoi(code);
                        }
                        catch(...){
                            cerr << "ERROR: address: '" << code <<"' not defined, line: "<< list[i][0] <<endl; 
                            abort = true;
                            return;
                        }
                        imm_value = true;
                    }
                    else{
                        //std::cout<<address_map.at(code)<<"| ";
                        value = address_map.at(code);
                        int targ = value;
                        imm_value = true;
                        if(type == 1 && opcode < 8){
                            value = ((value - address_pointer)/4) - 1;
                            std::cout<<"branch: "<< value <<" current address: "<<address_pointer<<" target: "<<targ<<endl; 
                        }
                    }
                } else {
                    // found
                    //std::cout<<register_map.at(code)<<"| ";
                    value = register_map.at(code);
                    imm_value = false;
                }
                count += 1;
            }

            if (type == 0){
                switch(count){
                    case 1:
                        //array<int, 3> inst = instruction_map.at(code);
                        func = inst[2];
                        break;
                    case 2:
                        if (func > 3) rs = value;
                        else rt = value;
                        break;
                    case 3:
                        if (func > 3) rt = value;
                        else rd = value;
                        break;
                    case 4:
                        if (func > 3) rd = value;
                        else shamt = value;
                        break;
                    default:
                        break;
                }
            }
            else if (type == 1){
                switch(count){
                    case 1:
                        //array<int, 3> inst = instruction_map.at(code);
                        opcode = inst[1];
                        break;
                    case 2:
                        rs = value;
                        break;
                    case 3:
                        if(imm_value){
                            imm = value;
                        }
                        else{
                            rt = value;
                        }
                        break;
                    case 4:
                        if(imm_value){
                            imm = value;
                        }
                        else{
                            rt = value;
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (type == 2){
                switch(count){
                    case 1:
                        //array<int, 3> inst = instruction_map.at(code);
                        opcode = inst[1];
                        break;
                    case 2:
                        target = value/4;
                        break;
                    default:
                        break;
                }
            }
        }
        
        address_pointer += 4;
        //std::cout<<endl;
        array<bool, 32> arr;

        switch(type){
            case 0:
                r_type_inst rinst = create_r_type_inst(opcode, rs, rt, rd, shamt, func);
                print_r_type_inst(rinst);
                
                for(int i = 0; i < 32; i++){
                    arr[i] = rinst.full[i];
                }
                instructions.push_back(arr);
                break;
            case 1:
                immediate_inst iinst = create_immediate_inst(opcode, rs, rt, imm);
                print_immediate_inst(iinst);

                for(int i = 0; i < 32; i++){
                    arr[i] = iinst.full[i];
                }
                instructions.push_back(arr);
                break;
            case 2:
                jump_inst jinst = create_jump_inst(opcode, target);
                print_jump_inst(jinst);
                for(int i = 0; i < 32; i++){
                    arr[i] = jinst.full[i];
                }
                instructions.push_back(arr);
                break;
            default:
                break;
        }
    }

    bool arr1[112][32] = {};

    for (int i = 0; i < num_insts; i++) {
        for(int j = 0; j < 32; j ++)
            arr1[i][j] = instructions[i][j];
    }
    cpu.load_instructions(arr1, num_insts);
    std::cout<<num_insts<<endl;
    if (pause_bool) pause();
}

void Assembler::run(int num, bool pause_bool){
    if (abort) return;
    cpu.execute_instructions(num);
    if (pause_bool) pause();
}

void Assembler::pause(){
    char buffer[5];

    do{
        std::cout<<"continue? y/n"<< endl;
        std::cin >> buffer;
    }
    while (buffer[0] != 'y');
}
void Assembler::show_registers(bool pause_bool){
    if (abort) return;
    cpu.print_registers();
    if (pause_bool) pause();
}
void Assembler::show_ram_data(bool pause_bool){
    if (abort) return;
    cpu.print_data();
    if (pause_bool) pause();
}
void Assembler::show_instructions(bool pause_bool){
    if (abort) return;
    cpu.print_instructions();
    if (pause_bool) pause();
}
