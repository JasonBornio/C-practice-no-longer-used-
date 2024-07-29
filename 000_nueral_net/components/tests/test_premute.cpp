#include "../permute.h"

int main()
{
    Array array1(4);
    array1.lin();
    array1.print();

    std::cout<<"array1 t():"<<std::endl;
    array1 = array1.t();
    array1.print();
    std::cout<<std::endl;

    Array array2(3, 2);
    array2.lin();
    array2.print();

    std::cout<<"array2 t():"<<std::endl;
    array2 = array2.t();
    array2.print();
    std::cout<<std::endl;

    Array array3(4, 3, 2);
    array3.lin();
    array3.print();

    std::cout<<"array3 t():"<<std::endl;
    array3 = array3.t();
    array3.print();
    std::cout<<std::endl;

    Array array4(2, 4, 3, 2);
    array4.lin();
    array4.print();

    std::cout<<"array4 t():"<<std::endl;
    array4 = array4.t();
    array4.print();
    std::cout<<std::endl;

    std::cout<<"array4 permute(3, 2, 1, 0):"<<std::endl;
    Array array5(2, 4, 3, 2);
    array5.lin();
    array5 = array5.permute(3,2,1,0);
    array5.print();
    std::cout<<std::endl;

    std::cout<<"array5: "<<std::endl;
    Array array6(4, 3, 2);
    array6.lin();
    array6.print();

    std::cout<<"array5 permute(1, 0, 2):"<<std::endl;
    array6 = array6.permute(1,0,2);
    array6.print();
    std::cout<<std::endl;
}