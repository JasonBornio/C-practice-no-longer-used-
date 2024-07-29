#include "../array.h"

int main()
{

    Array arr(5);
    Array arr2;
    //arr.set_name("array1");
    //arr2.set_name("array2");

    std::cout<<"zeros   : "<<std::endl;
    arr.zeros();
    arr.print();
    arr.print_grad();

    std::cout<<"ones   : "<<std::endl;
    arr.ones();
    arr.print();
    arr.print_grad();

    std::cout<<"rand   : "<<std::endl;
    arr.random();
    arr.print();
    arr.print_grad();

    float arr1[5] = {1.,2.,3.,4.,5.};

    std::cout<<"fill   : "<<std::endl;
    arr.fill_arr(arr1, 5);
    arr.print();
    arr.print_grad();

    std::cout<<" + 5   : "<<std::endl;
    arr2 = arr + 5.;
    arr2.print();
    arr2.print_grad();

    std::cout<<" - 2   : "<<std::endl;
    arr2 = arr - 2.;
    arr2.print();
    arr2.print_grad();

    std::cout<<" * 4   : "<<std::endl;
    arr2 = arr * 4.;
    arr2.print();
    arr2.print_grad();

    std::cout<<" / 10  : "<<std::endl;
    arr2 = arr / 10.;
    arr2.print();
    arr2.print_grad();

    std::cout<<" ^ 2   : "<<std::endl;
    arr2 = arr ^ 2.;
    arr2.print();
    arr2.print_grad();

    std::cout<<"arr[2]    : "<<arr2(2)<<std::endl;
    std::cout<<"arr[2] + 2: "<<arr2(2) + 2<<std::endl;
    std::cout<<"arr[2] - 2: "<<arr2(2) - 2<<std::endl;
    std::cout<<"arr[2] * 2: "<<arr2(2) * 2<<std::endl;
    std::cout<<"arr[2] / 2: "<<arr2(2) / 2<<std::endl;
    std::cout<<"arr[2] ^ 2: "<<pow(arr2(2), 2)<<std::endl;

    std::cout<<"rnd*2-1: "<<std::endl;
    Array arr3(15);
    //arr3.set_name("array3");
    arr3.random(); 
    arr3 = (arr3 * 2.) - 1.;
    arr3.print();
    arr3.print_grad();

    Array arr4(5);
    arr4.fill_arr(arr1, 5);

    std::cout<<"ones*10: "<<std::endl;
    arr.ones();
    arr = arr * 10;
    arr.print();
    arr.print_grad();

    std::cout<<"ar1+ar4: "<<std::endl;
    arr2 = arr + arr4;
    arr2.print();
    arr2.print_grad();

    std::cout<<"ar1-ar4: "<<std::endl;
    arr2 = arr - arr4;
    arr2.print();
    arr2.print_grad();

    std::cout<<"ar1*ar4: "<<std::endl;
    arr2 = arr * arr4;
    arr2.print();
    arr2.print_grad();

    std::cout<<"ar1/ar4: "<<std::endl;
    arr2 = arr / arr4;
    arr2.print();
    arr2.print_grad();

    Shape shp({3,2}, 2);
    shp.print();

    Shape shp1({4,3,2}, 3);
    shp1.print();

    std::cout<<"ar2 t(): "<<std::endl;
    arr2 = arr2.t();
    arr2.print();

    std::cout<<"ar2 t(): "<<std::endl;
    arr2 = arr2.t();
    arr2.print();



    return 0; 
}