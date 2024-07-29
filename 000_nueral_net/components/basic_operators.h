#include "fill_array.h"

Array Array::operator=(const Array& arr2){

    if (this == &arr2)
        return *this;

    this->data = arr2.data;
    this->dots = arr2.dots;
    this->shape = arr2.shape;
    this->rank = arr2.rank;
    //strcpy(arr2.name, this->name);
    
    return *this;
}
Array Array::operator+(float rhs){
    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] + rhs;
        arr.dots[i] = this->dots[i] + rhs;
    }

    return arr;
}
Array Array::operator-(float rhs){
    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] - rhs;
        arr.dots[i] = this->dots[i] - rhs;
    }

    return arr;
}
Array Array::operator/(float rhs){
    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] / rhs;
        arr.dots[i] = this->dots[i] / rhs;
    }

    return arr;
}
Array Array::operator*(float rhs){
    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] * rhs;
        arr.dots[i] = this->dots[i] * rhs;
    }

    return arr;
}
Array Array::operator^(int rhs){
    Array arr = this->create_arr();
    
    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = std::pow(this->data[i], rhs);
        arr.dots[i] = rhs * this->dots[i] * std::pow(this->data[i], rhs - 1);
    }

    return arr;
}

Array Array::operator+(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] + rhs.data[i];
        arr.dots[i] = this->dots[i] + rhs.dots[i];
    }

    return arr;
}
Array Array::operator-(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] - rhs.data[i];
        arr.dots[i] = this->dots[i] - rhs.dots[i];
    }

    return arr;
}
Array Array::operator/(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] / rhs.data[i];
        arr.dots[i] = (this->dots[i] * rhs.data[i] - this->data[i] * rhs.dots[i])/(rhs.data[i] * rhs.data[i]);
    }

    return arr;
}
Array Array::operator*(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array arr = this->create_arr();

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] * rhs.data[i];
        arr.dots[i] = (this->data[i] * rhs.dots[i]) + (this->dots[i] * rhs.data[i]);
    }

    return arr;
}
