#include <stdio.h>
#include <string.h>
#include <cstring>
#include "shape.h"
#include <math.h>

class Array {
    public:

        Array();
        Array(int _shape_0); //Array1;
        Array(int _shape_0, int _shape_1); //Array2
        Array(int _shape_0, int _shape_1, int _shape_2); //Array3
        Array(int _shape_0, int _shape_1, int _shape_2, int _shape_3); //Array4

        //basic ops
        Array operator=(const Array& arr2);
        Array operator+(float rhs);
        Array operator-(float rhs);
        Array operator/(float rhs);
        Array operator*(float rhs);
        Array operator^(int rhs);

        //array ops
        Array operator+(Array& rhs);
        Array operator-(Array& rhs);
        Array operator*(Array& rhs);
        Array operator/(Array& rhs);

        //access ops
        float& operator()(std::size_t idx_1);
        float& operator()(std::size_t idx_1, std::size_t idx_2);
        float& operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3);
        float& operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3, std::size_t idx_4);

        Array broadcast();

        Array reshape(int shape_0);
        Array reshape(int shape_0, int shape_1);
        Array reshape(int shape_0, int shape_1, int shape_2);
        Array reshape(int shape_0, int shape_1, int shape_2, int shape_3);
            
        
        Array permute(int dim1, int dim2);
        Array permute(int dim1, int dim2, int dim3);
        Array permute(int dim1, int dim2, int dim3, int dim4);
        Array t();
        Array dot(Array& rhs);
        std::vector<Array> split(int dim);

        void set_name(std::string string);

        void fill_arr(float _data[], int size);
        void fill_vec(std::vector<float> _data, int size);
        void fill_grad_vec(std::vector<float> _data, std::vector<float> _dots, int size);
        void ones();
        void random();
        void zeros();
        void lin();

        void print_grad();
        void print();

        Shape get_shape();
        std::vector<float> get_data();
        std::vector<float> get_grad();

        //void to_array2();

    private:
        char name[10];
        Shape shape;
        int rank;

        std::vector<float> data;
        std::vector<float> dots;

        Array create_arr();

        void print_arr2();
        void print_arr3();
        void print_arr4();

        Array try_dot_arr1(Array& rhs);
        Array try_dot_arr2(Array& rhs);
        Array try_dot_arr3(Array& rhs);
        Array try_dot_arr4(Array& rhs);
        
        Array try_dot(Array& lhs, Array& rhs);
};

void Array::set_name(std::string string){
    if (string.size() > 8) {
        std::cout << "that name is too long!"<< std::endl;
        return; 
    }

    if(8 > string.size())
        string.insert(0, 8 - string.size(), ' ');

    strcpy(this->name, string.c_str());
}

Shape Array::get_shape(){
    return this->shape;
}
std::vector<float> Array::get_data(){
    return this->data;
}
std::vector<float> Array::get_grad(){
    return this->dots;
}

