#include "../dot.h"

int main()
{
    std::cout<<"ARRAY1::::::::::: "<<std::endl;
    Array array1(4);
    array1.set_name("arr1");
    array1.lin();
    array1.print();

    Array array1_1(4);
    array1_1.set_name("arr2");
    array1_1 = array1.t();
    array1_1.print();

    Array result;
    result.set_name("result");

    //arr1.(arr1.t())
    std::cout<<"arr1.arr2"<<std::endl;
    result = array1.dot(array1_1);
    result.print();
    std::cout<<std::endl;

    //arr1.t().arr1
    std::cout<<"arr2.arr1"<<std::endl;
    result = array1_1.dot(array1);
    result.print();
    std::cout<<std::endl;

    std::cout<<"ARRAY2::::::::::: "<<std::endl;
    Array array2(2, 4);
    array2.set_name("arr3");
    array2.lin();
    array2.print();

    Array array2_1(4, 2);
    array2_1.set_name("arr4");
    array2_1.lin();
    array2_1.print();

    //arr2.(arr2.t())
    std::cout<<"arr3.arr4"<<std::endl;
    result = array2.dot(array2_1);
    result.print();
    std::cout<<std::endl;

    //arr2.t().arr2
    std::cout<<"arr4.arr3"<<std::endl;
    result = array2_1.dot(array2);
    result.print();
    std::cout<<std::endl;

    //arr1.(arr2.t())
    std::cout<<"arr1.arr4"<<std::endl;
    result = array1.dot(array2_1);
    result.print();
    std::cout<<std::endl;

    //arr2.(arr1.t())
    std::cout<<"arr3.arr2"<<std::endl;
    result = array2.dot(array1_1);
    result.print();
    std::cout<<std::endl;
    std::cout<<"ARRAY3::::::::::: "<<std::endl;

    Array array3(4, 2, 3);
    array3.set_name("arr5");
    array3.lin();
    array3.print();

    Array array3_1(3, 2, 4);
    array3_1.set_name("arr6");
    array3_1.lin();
    array3_1.print();


    //arr1.arr3
    std::cout<<"arr1.arr5"<<std::endl;
    result = array1.dot(array3);
    result.print();
    std::cout<<std::endl;
    
    //arr3.permute().(arr1.t())
    std::cout<<"arr5.arr2"<<std::endl;
    array3 = array3.permute(2,1,0);
    result = array3.dot(array1_1);
    result.print();
    std::cout<<std::endl;

    //arr3.permute().(arr2.t())
    std::cout<<"arr5.arr4"<<std::endl;
    result = array3.dot(array2_1);
    result.print();
    std::cout<<std::endl;

    //arr3.t().(arr2)
    std::cout<<"arr5.arr4"<<std::endl;
    array3 = array3.permute(2,1,0);
    array3 = array3.t();
    //array3.print();
    result = array3.dot(array2);
    result.print();
    std::cout<<std::endl;

    array3 = array3.t();

    //arr3.(arr3.t())
    std::cout<<"arr5.arr4"<<std::endl;
    result = array3.dot(array3_1);
    result.print();
    std::cout<<std::endl;

    //arr3.t().arr3
    std::cout<<"arr5.arr4"<<std::endl;
    result = array3_1.dot(array3);
    result.print();
    std::cout<<std::endl;

    std::cout<<"ARRAY4::::::::::: "<<std::endl;

    Array array4(5, 4, 3, 2);
    array4.set_name("arr7");
    array4.lin();
    array4.print();

    Array array4_1(2, 3, 4, 5);
    array4_1.set_name("arr8");
    array4_1.lin();
    array4_1.print();

    
}