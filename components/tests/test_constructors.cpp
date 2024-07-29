#include "../constructors.h"

int main()
{
    Array empty_arr;

    Array array1(100);
    std::cout<<"array1 shape: "
        <<array1.get_shape().shape()[0]<<", "
        <<array1.get_shape().shape()[1]
        <<std::endl;
        
    Array array2(10, 10);
    std::cout<<"array2 shape: "
        <<array2.get_shape().shape()[0]<<", "
        <<array2.get_shape().shape()[1]
        <<std::endl;

    Array array3(10, 5, 2);
    std::cout<<"array3 shape: "
        <<array3.get_shape().shape()[0]<<", "
        <<array3.get_shape().shape()[1]<<", "
        <<array3.get_shape().shape()[2]
        <<std::endl;

    Array array4(2, 5, 5, 2);
    std::cout<<"array4 shape: "
        <<array4.get_shape().shape()[0]<<", "
        <<array4.get_shape().shape()[1]<<", "
        <<array4.get_shape().shape()[2]<<", "
        <<array4.get_shape().shape()[3]
        <<std::endl;

}