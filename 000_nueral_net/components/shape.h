#include <vector>
#include <iostream>

class Shape {
    public:

        Shape();
        Shape(std::vector<int> _dims, int _num_dims);
        Shape(int _dims[], int _num_dims);

        void permute(int _dims[], int num);

        // Shape operator=(const Shape& s2);
        std::vector<int> shape();
        std::vector<int> strides();
        int size();
        int dims();
        void print();

    private:
        int num_dims;
        std::vector<int> dims_vec;
        std::vector<int> strides_vec;
        int size_flat;

};

Shape::Shape(){

}

Shape::Shape(std::vector<int> _dims, int _num_dims){
    if(_num_dims > 4){
        std::cout<<"This shape is not supported"<<std::endl;
        return;
    }

    this->dims_vec = _dims;
    this->num_dims = _num_dims;

    this->size_flat = 1;
    this->strides_vec = std::vector<int>(_num_dims, 1);
    this->strides_vec[_num_dims - 1] = 1;

    for (int i = 0; i < _num_dims; i++){
        this->size_flat *= _dims[i];
        if (i > 0) this->strides_vec[_num_dims - i - 1] = strides_vec[_num_dims - i] * _dims[_num_dims - i];
    }
}

Shape::Shape(int _dims[], int _num_dims){
    if(_num_dims > 4){
        std::cout<<"This shape is not supported"<<std::endl;
        return;
    }

    this->num_dims = _num_dims;

    this->size_flat = 1;
    this->strides_vec = std::vector<int>(_num_dims, 1);
    this->strides_vec[_num_dims - 1] = 1;

    for (int i = 0; i < _num_dims; i++){
        this->size_flat *= _dims[i];
        this->dims_vec.push_back(_dims[i]);
        if (i > 0) this->strides_vec[_num_dims - i - 1] = strides_vec[_num_dims - i] * _dims[_num_dims - i];
    }
}

void Shape::permute(int _dims[], int num){
    
    std::vector<int> new_shape(num, 0);
    this->strides_vec[this->num_dims - 1] = 1;

    for(int i = 0; i < this->num_dims; i++){
        new_shape[i] = this->dims_vec[_dims[i]];
    }

    for(int i = 1; i < this->num_dims; i++){
        this->strides_vec[this->num_dims - i - 1] = strides_vec[this->num_dims - i] * new_shape[num - i];
    }

    this->dims_vec = new_shape;
}

// Shape Shape::operator=(const Shape& s2){
//     return s2;
// }

std::vector<int> Shape::shape(){
    return this->dims_vec;
}

std::vector<int> Shape::strides(){
    return strides_vec;
}

int Shape::size(){
    return size_flat;
}

int Shape::dims(){
    return  num_dims;
}

void Shape::print(){
    std::cout<<"shape: (";

    for (int i = 0; i < this->num_dims; i++){
        std::cout<<this->dims_vec[i];
        if (i < this->num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), strides: (";

    for (int i = 0; i < this->num_dims; i++){
        std::cout<<this->strides_vec[i];
        if (i < this->num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), size: "<<this->size_flat<<std::endl;
}