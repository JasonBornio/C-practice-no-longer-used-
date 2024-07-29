#include "constructors.h"

void Array::print(){
    switch(this->rank){
        case 1:
            this->print_arr2();
            break;
        case 2:
            this->print_arr2();
            break;
        case 3:
            this->print_arr3();
            break;
        case 4:
            this->print_arr4();
            break;
        default:
            std::cout<<"No print method availble for this array!";
            exit(0);
            break;

    }
}

void Array::print_arr2(){
    std::vector<int> strides = this->shape.strides();
    std::vector<int> shape = this->shape.shape();

    std::cout<<this->name<<" : ({ ";

    for (int j = 0; j < shape[0]; j++){
        if (shape[0] > 1 && j > 0) std::cout<<std::endl<<"            ";
        std::cout<<"[";
        for (int i = 0; i < shape[1]; i++){
            std::cout<<this->data[strides[0] * j + i];
            if (i < shape[1] - 1) std::cout<<", ";
        }
        std::cout<<"]";
        if (j < shape[0] - 1) std::cout<<", ";
    }

    std::cout<<" }, ";
    
    std::cout<<"shape: (";

    int num_dims = this->shape.dims();

    for (int i = 0; i < num_dims; i++){
        std::cout<<shape[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), strides: (";

    for (int i = 0; i < num_dims; i++){
        std::cout<<strides[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), rank:"<<this->rank<<")"<<std::endl;
}
void Array::print_arr3(){
    std::vector<int> strides = this->shape.strides();
    std::vector<int> shape = this->shape.shape();

    std::cout<<this->name<<" : ({ ";
    for(int k = 0; k < shape[0]; k++){
        if (shape[2] > 1 && k > 0) std::cout<<std::endl<<"            ";
        std::cout<<"[";
        for (int j = 0; j < shape[1]; j++){
            if (shape[1] > 1 && j > 0) std::cout<<std::endl<<"            ";
            if(j > 0) std::cout<<" ";
            std::cout<<"[";
            for (int i = 0; i < shape[2]; i++){
                std::cout<<this->data[strides[0] * k + strides[1] * j + i];
                if (i < shape[2] - 1) std::cout<<", ";
            }
            std::cout<<"]";
            //if (j < shape[1] - 1) std::cout<<", ";
        }
        std::cout<<"]";
        if (k < shape[0] - 1) std::cout<<", "<<std::endl;
    }

    std::cout<<" }, ";
    
    std::cout<<"shape: (";

    int num_dims = this->shape.dims();

    for (int i = 0; i < num_dims; i++){
        std::cout<<shape[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), strides: (";

    for (int i = 0; i < num_dims; i++){
        std::cout<<strides[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), rank:"<<this->rank<<")"<<std::endl;
}
void Array::print_arr4(){
    std::vector<int> strides = this->shape.strides();
    std::vector<int> shape = this->shape.shape();

    std::cout<<this->name<<" : ({ ";
    for (int l = 0; l < shape[0]; l++){ 
        if (shape[3] > 1 && l > 0) std::cout<<std::endl<<"            ";
        std::cout<<"[";
        
        for(int k = 0; k < shape[1]; k++){ 
            if (shape[2] > 1 && k > 0) std::cout<<std::endl<<"            ";
            if(k > 0) std::cout<<" ";
            std::cout<<"[";

            for (int j = 0; j < shape[2]; j++){
                if (shape[1] > 1 && j > 0) std::cout<<std::endl<<"            ";
                if(j > 0) std::cout<<"  ";
                std::cout<<"[";

                for (int i = 0; i < shape[3]; i++){
                    std::cout<<this->data[strides[0] * l + strides[1] * k + strides[2] * j + i];
                    if (i < shape[3] - 1) std::cout<<", ";
                }

                std::cout<<"]";
                //if (j < shape[1] - 1) std::cout<<", ";
            }

            std::cout<<"]";
            if (k < shape[1] - 1) std::cout<<std::endl;
        }
        
        std::cout<<"]";
        if (l < shape[2] - 1) std::cout<<", "<<std::endl;
    }

    std::cout<<" }, ";
    
    std::cout<<"shape: (";

    int num_dims = this->shape.dims();

    for (int i = 0; i < num_dims; i++){
        std::cout<<shape[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), strides: (";

    for (int i = 0; i < num_dims; i++){
        std::cout<<strides[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), rank:"<<this->rank<<")"<<std::endl;
}

void Array::print_grad(){
    std::cout<<this->name<<"_g:({";

    for (int i = 0; i < this->shape.size(); i++){
        std::cout<<this->dots[i];
        if (i < this->shape.size() - 1) std::cout<<", ";
    }

    std::cout<<"}, ";
    
    std::cout<<"shape: (";

    int num_dims = shape.dims();

    for (int i = 0; i < num_dims; i++){
        std::cout<<this->shape.shape()[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"), strides: (";

    for (int i = 0; i < num_dims; i++){
        std::cout<<this->shape.strides()[i];
        if (i < num_dims - 1) std::cout<<", ";
    }

    std::cout<<"))"<<std::endl;
}
