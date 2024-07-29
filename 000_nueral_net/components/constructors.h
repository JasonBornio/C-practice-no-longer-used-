#include "array_object.h"

Array::Array(){
}

Array::Array(int _shape){
    Shape s({1, _shape}, 2);
    this->shape = s;
    this->rank = 1;
    strcpy(this->name, "array1");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}
Array::Array(int _shape_0, int _shape_1){
    Shape s({_shape_0, _shape_1}, 2);
    this->shape = s;
    this->rank = 2;
    strcpy(this->name, "array2");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}
Array::Array(int _shape_0, int _shape_1, int _shape_2){
    Shape s({_shape_0, _shape_1, _shape_2}, 3);
    this->shape = s;
    this->rank = 3;
    strcpy(this->name, "array3");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}
Array::Array(int _shape_0, int _shape_1, int _shape_2, int _shape_3){
    Shape s({_shape_0, _shape_1, _shape_2, _shape_3}, 4);
    this->shape = s;
    this->rank = 4;
    strcpy(this->name, "array4");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}

Array Array::create_arr(){
    std::vector<int> shape = this->get_shape().shape();

    switch(this->rank){
        case 1:
            return Array(this->shape.size());
        case 2:
            return Array(shape[0],shape[1]);
        case 3:
            return Array(shape[0], shape[1], shape[2]);
        case 4:
            return Array(shape[0], shape[1], shape[2], shape[3]);
        default:
            return Array(this->shape.size());
    }
}
