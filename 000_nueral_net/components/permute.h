#include "reshape.h"

Array Array::t(){
    Array arr = *this;

    switch(arr.rank){
        case 1:
            arr = arr.permute(1, 0);
            break;
        case 2:
            arr = arr.permute(1, 0);
            break;
        case 3:
            arr = arr.permute(0, 2, 1);
            break;
        case 4:
            arr = arr.permute(0, 1, 3, 2);
            break;
        default:
            std::cout<<"Invalid rank";
            exit(0);
            break;
    }

    return arr;
}
 
Array Array::permute(int dim1, int dim2){

    if (this->rank > 2) {
        std::cout << "Dimension mismatch: "<<this->rank<<" dims needed";
        exit(0);
    }

    Array arr = *this;

    std::vector<float> new_data(arr.shape.size(), 0.);
    std::vector<float> new_dots(arr.shape.size(), 0.);

    int count = 0;

    for (int j = 0; j < arr.shape.shape()[dim1]; j++){
        for (int i = 0; i < arr.shape.shape()[dim2]; i++){
            new_data[count] = arr.data[j * arr.shape.strides()[dim1] + i * arr.shape.strides()[dim2]];
            new_dots[count] = arr.dots[j * arr.shape.strides()[dim1] + i * arr.shape.strides()[dim2]];
            count+=1;
        }
    }

    int dims[2] = {dim1,dim2};
    arr.shape.permute(dims, 2);

    arr.data = new_data;
    arr.dots = new_dots;

    return arr;
}
Array Array::permute(int dim1, int dim2, int dim3){

    if (this->rank != 3) {
        std::cout << "Dimension mismatch: "<<this->rank<<" dims needed";
        exit(0);
    }

    Array arr = *this;

    std::vector<float> new_data(arr.shape.size(), 0.);
    std::vector<float> new_dots(arr.shape.size(), 0.);

    int count = 0;

    for (int k = 0; k < arr.shape.shape()[dim1]; k++){
        for (int j = 0; j < arr.shape.shape()[dim2]; j++){
            for (int i = 0; i < arr.shape.shape()[dim3]; i++){
                new_data[count] = arr.data[k * arr.shape.strides()[dim1] + j * arr.shape.strides()[dim2] + i * arr.shape.strides()[dim3]];
                new_dots[count] = arr.dots[k * arr.shape.strides()[dim1] + j * arr.shape.strides()[dim2] + i * arr.shape.strides()[dim3]];
                count+=1;
            }
        }
    }

    int dims[3] = {dim1,dim2, dim3};
    arr.shape.permute(dims, 3);

    arr.data = new_data;
    arr.dots = new_dots;

    return arr;
}
Array Array::permute(int dim1, int dim2, int dim3, int dim4){

    if (this->rank != 4) {
        std::cout << "Dimension mismatch: "<<this->rank<<" dims needed";
        exit(0);
    }

    Array arr = *this;

    std::vector<float> new_data(arr.shape.size(), 0.);
    std::vector<float> new_dots(arr.shape.size(), 0.);

    int count = 0;

    for (int l = 0; l < arr.shape.shape()[dim1]; l++){
        for (int k = 0; k < arr.shape.shape()[dim2]; k++){
            for (int j = 0; j < arr.shape.shape()[dim3]; j++){
                for (int i = 0; i < arr.shape.shape()[dim4]; i++){
                    new_data[count] = arr.data[l * arr.shape.strides()[dim1] + k * arr.shape.strides()[dim2] + j * arr.shape.strides()[dim3] + i * arr.shape.strides()[dim4]];
                    new_dots[count] = arr.dots[l * arr.shape.strides()[dim1] + k * arr.shape.strides()[dim2] + j * arr.shape.strides()[dim3] + i * arr.shape.strides()[dim4]];
                    count+=1;
                }
            }
        }
    }

    int dims[4] = {dim1,dim2,dim3,dim4};
    arr.shape.permute(dims, 4);

    arr.data = new_data;
    arr.dots = new_dots;

    return arr;
}