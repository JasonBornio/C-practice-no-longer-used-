#include "../print.h"

int main()
{
    Array empty_arr;
    //empty_arr.print();

    Array array1(2);
    array1.print();
    std::cout<<std::endl;

    Array array2(2, 3);
    array2.print();
    std::cout<<std::endl;

    Array array3(2, 3, 4);
    array3.print();
    std::cout<<std::endl;
    
    Array array4(2, 3, 4, 5);
    array4.print();

    empty_arr.print();

}