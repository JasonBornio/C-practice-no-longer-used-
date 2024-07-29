#include "../access_operators.h"

int main()
{
    Array array1(16);
    array1.lin();
    array1.print();
    std::cout<<"array1[2]: "<<array1(2)<<std::endl<<std::endl;

    Array array2(2, 4);
    array2.lin();
    array2.print();
    std::cout<<"array2[1][2]: "<<array2(1, 2)<<std::endl<<std::endl;
    
    Array array3(2, 4, 5);
    array3.lin();
    array3.print();
    std::cout<<"array3[1][2][3]: "<<array3(1, 2, 3)<<std::endl<<std::endl;
    
    Array array4(2, 4, 5, 6);
    array4.lin();
    array4.print();
    std::cout<<"array4[1][2][3][4]: "<<array4(1, 2, 3, 4)<<std::endl<<std::endl;

}