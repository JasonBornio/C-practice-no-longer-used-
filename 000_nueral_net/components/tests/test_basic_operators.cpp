#include "../basic_operators.h"

int main()
{
    Array array1(16);
    array1.lin();
    array1.print();
    Array array1_1(16);
    array1_1.ones();
    array1_1.set_name("array1_1");
    array1_1.print();

    array1 = array1 + array1_1;

    std::cout<<"array1 + array1_1: " <<std::endl;
    array1.print();

    std::cout<<"array1 + 5: " <<std::endl;
    array1_1 = array1 + 5;
    array1_1.print();

    std::cout<<"array1 - 5: " <<std::endl;
    array1_1 = array1 - 5;
    array1_1.print();

    std::cout<<"array1 * 5: " <<std::endl;
    array1_1 = array1 * 5;
    array1_1.print();

    std::cout<<"array1 / 5: " <<std::endl;
    array1_1 = array1 / 5;
    array1_1.print();

    std::cout<<"array1 ^ 3: " <<std::endl;
    array1_1 = array1 ^ 3;
    array1_1.print();

    std::cout<<std::endl;

    Array array2(4,4);
    array2.zeros();
    array2.print();

    std::cout<<"array2 * array1: " <<std::endl;
    array2 = array2 + array1;
    array2.print();

    std::cout<<"array2 / array1: " <<std::endl;
    array2 = array2 / array1;
    array2.print();

    std::cout<<"array2 * array1: " <<std::endl;
    array2 = array2 * array1;
    array2.print();
    std::cout<<std::endl;

    Array array4(2,2,2,2);
    array4.ones();
    array4.print();

    std::cout<<"array4 - array1: " <<std::endl;
    array4 = array4 - array1;
    array4.print();


}