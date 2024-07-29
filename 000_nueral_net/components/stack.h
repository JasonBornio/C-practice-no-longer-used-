#include "permute.h"

std::vector<Array> Array::split(int dim){
    Shape shape = this->shape;
    std::vector<int> dims = shape.shape();
    dims.erase(dims.begin() + dim); 
    int split_size = shape.shape()[dim];
    int elem_size = shape.size() / split_size;

    std::vector<Array> arrays;
    std::vector<float> data(elem_size, 0.);
    std::vector<float> dots(elem_size, 0.);

    Array ref = *this;

    switch(this->rank){
        case 2:
            if (dim) ref = this->t();
            break;
        case 3:
            if (dim == 1) ref = this->permute(1, 0, 2); 
            if (dim == 2) ref = this->permute(2, 0, 1); 
            break;
        case 4:
            if (dim == 1) ref = this->permute(1, 0, 2, 3); 
            if (dim == 2) ref = this->permute(2, 0, 1, 3); 
            if (dim == 3) ref = this->permute(3, 0, 1, 2); 
            break;
        default:
            std::cout<<"Invalid rank!"<<std::endl;
            exit(0);
            break;
    }  

    std::vector<int> strides = ref.get_shape().strides();

    for(int j = 0; j < split_size; j++){
        Array elem_array(elem_size);

        switch(this->rank){
            case 2:
                elem_array.reshape(dims[0]);
                break;
            case 3:
                elem_array.reshape(dims[0], dims[1]);
                break;
            case 4:
                elem_array.reshape(dims[0], dims[1], dims[2]);
                break;
            default:
                std::cout<<"NAHHHHHH!"<<std::endl;
                exit(0);
                break;
        }   


        for (int i = 0; i < elem_size; i++){
            data[i] = ref.data[strides[0] * j + i];
            dots[i] = ref.dots[strides[0] * j + i];
        }
        elem_array.fill_grad_vec(data, dots, elem_size);
        arrays.push_back(elem_array);
    }

    return arrays;
}

Array stack(std::vector<Array> arrays, int size, int dim){
    Shape arr_shape = arrays[0].get_shape();
    int array_size = arr_shape.size();
    int total_d_size = size * array_size;
    int num_dim = arr_shape.dims();
    std::vector<int> shape = arr_shape.shape();

    shape.insert(shape.begin(), size);
    Array stacked_array(total_d_size);

    switch(num_dim + 1){
        case 2:
            stacked_array.reshape(shape[0], shape[1]);
            break;
        case 3:
            stacked_array.reshape(shape[0], shape[1], shape[2]);
            break;
        case 4:
            stacked_array.reshape(shape[0], shape[1], shape[2], shape[3]);
            break;
        default:
            std::cout<<"Invalid rank!"<<std::endl;
            exit(0);
            break;
    }

    std::vector<int> strides = stacked_array.get_shape().strides();

    std::vector<float> stacked_data(total_d_size, 0.);
    std::vector<float> stacked_dots(total_d_size, 0.);

    for(int j = 0; j < size; j++){
        std::vector<float> data = arrays[j].get_data();
        std::vector<float> dots = arrays[j].get_grad();
        for (int i = 0; i < array_size; i++){
            stacked_data[strides[0] * j + i] = data[i];
            stacked_dots[strides[0] * j + i] = dots[i];
        }
    }

    stacked_array.fill_grad_vec(stacked_data, stacked_dots, total_d_size);
    
    switch(num_dim + 1){
        case 2:
            if (dim) stacked_array = stacked_array.t(); 
            break;
        case 3:
            if (dim == 1) stacked_array = stacked_array.permute(1, 0, 2); 
            if (dim == 2) stacked_array = stacked_array.permute(1, 2, 0); 
            break;
        case 4:
            if (dim == 1) stacked_array = stacked_array.permute(1, 0, 2, 3); 
            if (dim == 2) stacked_array = stacked_array.permute(1, 2, 0, 3); 
            if (dim == 3) stacked_array = stacked_array.permute(1, 2, 3, 0); 
            break;
        default:
            std::cout<<"NAHHHHHH!"<<std::endl;
            exit(0);
            break;
    }
    return stacked_array;
}