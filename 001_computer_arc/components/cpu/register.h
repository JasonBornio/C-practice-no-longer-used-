#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "instruction.h"

class Reg_32 {
    public:
        Reg_32();

        //Reg_32 operator=(const Reg_32& r2);

        Reg_32 operator|(const Reg_32& r2);
        Reg_32 operator&(const Reg_32& r2);
        Reg_32 operator^(const Reg_32& r2);
        Reg_32 operator~();
        void copy(Reg_32& r2);

        void set_name(std::string string);
        void print();

        void fill_arr_upper(bool _data[], int size);
        void fill_arr_lower(bool _data[], int size);
        void fill_arr_lower(bool _data[], int size, int offset);
        void fill_ones_upper(int size);
        void fill_ones_lower(int size);
        void clear();

        bool get_data(int index);
        int get_data();
        void get_data_arr(bool arr[32]);

    private:
        char name[10];
        bool data[32] = { };

};

Reg_32::Reg_32(){
    strcpy(this->name, "register");
}

// Reg_32 Reg_32::operator=(const Reg_32& r2){

//     Reg_32 reg;

//     for(int i = 0; i < g_dim; i++){
//         reg.data[i] = r2.data[i];
//     } 
    
//     strcpy(reg.name, r2.name);

//     return reg;
// }

Reg_32 Reg_32::operator|(const Reg_32& r2){
    Reg_32 reg;

    for(int i = 0; i < constants::g_dim; i++){
        reg.data[i] = this->data[i] || r2.data[i];
    } 

    return reg;
}

Reg_32 Reg_32::operator&(const Reg_32& r2){
    Reg_32 reg;

    for(int i = 0; i < constants::g_dim; i++){
        reg.data[i] = this->data[i] && r2.data[i];
    } 

    return reg;
}

Reg_32 Reg_32::operator^(const Reg_32& r2){
    Reg_32 reg;

    for(int i = 0; i < constants::g_dim; i++){
        reg.data[i] = this->data[i] ^ r2.data[i];
    } 

    return reg;
}

Reg_32 Reg_32::operator~(){
    Reg_32 reg;

    for(int i = 0; i < constants::g_dim; i++){
        reg.data[i] = !this->data[i];
    } 

    return reg;
}

void Reg_32::copy(Reg_32& r2){
    for(int i = 0; i < constants::g_dim; i++){
        this->data[i] = r2.data[i];
    } 

    //this->set_name(r2.name);
}

void Reg_32::set_name(std::string string){
    if (string.size() > 8) {
        std::cout << "that name is too long!"<< std::endl;
        return; 
    }

    if(8 > string.size())
        string.insert(0, 8 - string.size(), ' ');

    strcpy(this->name, string.c_str());
}


void Reg_32::print(){

    std::cout << this->name <<": { ";

    for (int i = 0; i < constants::g_dim; i++){
        std::cout << int(this->data[i]);
    }

    std::cout <<", val: "<< get_data() << " }"<< std::endl;
}

void Reg_32::fill_arr_upper(bool _data[], int size){
    if (size > constants::g_dim) {size = constants::g_dim;}

    for (int i = 0; i < size; i++){
        this->data[i] = _data[i];
    }
}

void Reg_32::fill_arr_lower(bool _data[], int size){
    if (size > constants::g_dim) {size = constants::g_dim;}

    for (int i = 0; i < size; i++){
        this->data[(constants::g_dim) - size + i] = _data[i];
    }
}

void Reg_32::fill_arr_lower(bool _data[], int size, int offset){
    int total_size = size + offset; 
    if (size > constants::g_dim) {size = constants::g_dim;}
    if (total_size > constants::g_dim) {total_size = constants::g_dim;}

    for (int i = 0; i < size; i++){
        this->data[(constants::g_dim) - total_size + i] = _data[i];
    }
}

void Reg_32::fill_ones_upper(int size){
    if (size > constants::g_dim) {size = constants::g_dim;}

    for (int i = 0; i < size; i++){
        this->data[i] = true;
    }
}

void Reg_32::fill_ones_lower(int size){
    if (size > constants::g_dim) {size = constants::g_dim;}

    for (int i = 0; i < size; i++){
        this->data[(constants::g_dim) - size + i] = true;
    }
}

void Reg_32::clear(){
    for (int i = 0; i < constants::g_dim; i++){
        this->data[i] = false;
    }
}

bool Reg_32::get_data(int index){
    return this->data[index];
}

int Reg_32::get_data(){
    return bin_to_int(this->data, constants::g_dim);
}

void Reg_32::get_data_arr(bool arr[32]){
    for (int i = 0; i < 32; ++i) {
        arr[i] = this->data[i];
    }
}
