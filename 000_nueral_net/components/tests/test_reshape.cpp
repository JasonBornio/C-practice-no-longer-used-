#include "../reshape.h"

int main()
{
    Array array1(16);
    array1.random();
    array1.print();
    std::cout<<std::endl;

    array1.reshape(4,4);
    array1.print();
    std::cout<<std::endl;

    array1.reshape(2,2,4);
    array1.print();
    std::cout<<std::endl;

    array1.reshape(2,2,2,2);
    array1.print();
    std::cout<<std::endl;

    Array array2(2,2,3,4);
    array2.lin();
    array2.print();
    std::cout<<std::endl;

    array2.reshape(2,2,12);
    array2.print();
    std::cout<<std::endl;

    array2.reshape(2,24);
    array2.print();
    std::cout<<std::endl;

    array2.reshape(48);
    array2.print();
    
}