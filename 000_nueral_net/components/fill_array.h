#include "to_array.h"

void Array::fill_arr(float _data[], int size){
    if (size > this->shape.size()) size = this->shape.size();
    int remainder = size - this->shape.size();

    for(int i = 0; i < size; i++){
        data[i] = _data[i];
        dots[i] = 1.;
    }

    // for(int i = 0; i < remainder; i++){
    //     data[size + i] = 0.;
    //     dots[size + i] = 1.;
    // }
}
void Array::fill_vec(std::vector<float> _data, int size){
    if (size > this->shape.size()) size = this->shape.size();
    int remainder = size - this->shape.size();

    for(int i = 0; i < size; i++){
        data[i] = _data[i];
        dots[i] = 1.;
    }

    // for(int i = 0; i < remainder; i++){
    //     data[size + i] = 0.;
    //     dots[size + i] = 1.;
    // }
}
void Array::fill_grad_vec(std::vector<float> _data, std::vector<float> _dots, int size){
    if (data.size() != dots.size()) {
        std::cout << "Data and gradient vectors mus be the same size";
        exit(0);
    }
    if (size > this->shape.size()) size = this->shape.size();
    int remainder = size - this->shape.size();

    for(int i = 0; i < size; i++){
        data[i] = _data[i];
        dots[i] = _dots[i];
    }

    // for(int i = 0; i < remainder; i++){
    //     data[size + i] = 0.;
    //     dots[size + i] = 1.;
    // }
}


void Array::ones(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = 1.;
        dots[i] = 1.;
    }
}
void Array::random(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float((std::rand() % 1000) + 1)/1000;
        dots[i] = 1.;
    }
}
void Array::zeros(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = 0.;
        dots[i] = 1.;
    }
}
void Array::lin(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float(i);
        dots[i] = 1.;
    }
}