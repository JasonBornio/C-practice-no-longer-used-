#include "../fill_array.h"

int main()
{

    float arr[16] = {3.,5.,3.,4.,7.,6.,7.,8.,9.,10.,11.,12.,21.,30.,15.,16};
    std::vector<float> vec(32, 5.);

    Array array1(16);
    array1.fill_arr(arr, 16);

    std::cout<<"fill_arr:"<<std::endl;
    array1.print();

    array1.fill_vec(vec, 10);
    std::cout<<"fill_vec:"<<std::endl;    
    array1.print();
    std::cout<<std::endl;    

    Array array2(2, 3);
    
    array2.ones();
    std::cout<<"ones:"<<std::endl;    
    array2.print();
    
    array2.zeros();
    std::cout<<"zeros:"<<std::endl;    
    array2.print();
    std::cout<<std::endl;    

    Array array3(2, 3, 4);
    
    array3.lin();
    std::cout<<"lin:"<<std::endl;    
    array3.print();
    std::cout<<std::endl;    

    Array array4(2, 3, 4, 5);
    
    array4.random();
    std::cout<<"random:"<<std::endl;    
    array4.print();
    


}