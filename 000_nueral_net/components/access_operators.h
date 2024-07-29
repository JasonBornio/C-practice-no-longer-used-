#include "basic_operators.h"

float& Array::operator()(std::size_t idx_1){
    if (this->rank != 1) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.size()) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }
    return data[idx_1];
}

float& Array::operator()(std::size_t idx_1, std::size_t idx_2){
    if (this->rank != 2) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.shape()[0] || idx_2 >= this->shape.shape()[1]) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }

    return data[(idx_1 * this->shape.strides()[0]) + idx_2];
}

float& Array::operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3){
    if (this->rank != 3) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.shape()[0] || idx_2 >= this->shape.shape()[1] || idx_3 >= this->shape.shape()[2]) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }

    return data[(idx_1 * this->shape.strides()[0]) + (idx_2 * this->shape.strides()[1]) + idx_3];
}


float& Array::operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3, std::size_t idx_4){
    if (this->rank != 4) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.shape()[0] || idx_2 >= this->shape.shape()[1] || idx_3 >= this->shape.shape()[2] || idx_4 >= this->shape.shape()[3]) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }

    return data[(idx_1 * this->shape.strides()[0]) + (idx_2 * this->shape.strides()[1]) + (idx_3 * this->shape.strides()[2]) + idx_4];
}

