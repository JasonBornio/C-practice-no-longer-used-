#include "../array.h"

int main()
{

    Array arr(2, 5);
    Array arr2;
    
    //arr.set_name("Array2");
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

    float arr1[10] = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10};
    

    std::cout<<"fill   : "<<std::endl;
    arr.fill_arr(arr1, 10);
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


    std::cout<<"arr[1][2]    : "<<arr2(1, 2)<<std::endl;
    std::cout<<"arr[1][3] + 2: "<<arr2(1, 3) + 2<<std::endl;
    std::cout<<"arr[1][3] - 2: "<<arr2(1, 3) - 2<<std::endl;
    std::cout<<"arr[1][2] * 2: "<<arr2(1, 2) * 2<<std::endl;
    std::cout<<"arr[1][3] / 2: "<<arr2(1, 3) / 2<<std::endl;
    std::cout<<"arr[1][3] ^ 2: "<<pow(arr2(1, 3), 2)<<std::endl;

    std::cout<<"rnd*2-1: "<<std::endl;
    Array arr3(3,5);
    //arr3.set_name("array3");
    arr3.random(); 
    arr3 = (arr3 * 2.) - 1.;
    arr3.print();
    arr3.print_grad();

    Array arr4(2, 5);
    arr4.fill_arr(arr1, 10);

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

    arr2.fill_arr(arr1, 10);
    arr2.print();
    //arr2.print_grad();

    std::cout<<"ar2 t(): "<<std::endl;
    arr2 = arr2.t();
    arr2.print();
    //arr2.print_grad();

    std::cout<<"ar2 t(): "<<std::endl;
    arr2 = arr2.t();
    arr2.print();
    //arr2.print_grad();

    Array arr5(3,3);

    std::cout<<"ar5    : "<<std::endl;
    arr5.fill_arr(arr1, 9);
    arr5.print();

    std::cout<<"ar5 t(): "<<std::endl;
    arr5 = arr5.t();
    arr5.print();

    Array arr6(2,3);
    Array arr7(3,2);

    arr6.fill_arr(arr1, 6);
    arr7.fill_arr(arr1, 6);


    std::cout<<"ar6    : "<<std::endl;
    arr6.print();

    std::cout<<"ar7    : "<<std::endl;
    arr7.print();

    Array arr8 = arr6.dot(arr7);
    std::cout<<"ar6.ar7: "<<std::endl;
    arr8.print();

    arr8 = arr7.dot(arr6);
    std::cout<<"ar7.ar6: "<<std::endl;
    arr8.print();

    Array arr9(3);
    arr9.fill_arr(arr1, 3);
    arr2 = arr9.t();
    std::cout<<"ar9    : "<<std::endl;
    arr9.print();
    std::cout<<"ar10   : "<<std::endl;
    arr2.print();

    arr8 = arr9.dot(arr7);
    std::cout<<"ar9.ar7: "<<std::endl;
    arr8.print();

    arr8 = arr6.dot(arr2);
    std::cout<<"ar6.a10: "<<std::endl;
    arr8.print();


    arr8 = arr9.dot(arr2);
    std::cout<<"ar9.a10: "<<std::endl;
    arr8.print();

    arr8 = arr2.dot(arr9);
    std::cout<<"a10.ar2: "<<std::endl;
    arr8.print();

    Array arr11(40);
    arr11.random();

    std::cout<<"arr11  : "<<std::endl;
    arr11.print();

    std::cout<<"arr11  : "<<std::endl;
    arr11.reshape(2, 20);
    arr11.print();

    std::cout<<"arr11  : "<<std::endl;
    arr11.reshape(4, 2, 5);
    arr11.print();

    std::cout<<"arr11  : "<<std::endl;
    arr11.reshape(2, 2, 2, 5);
    arr11.print();


    return 0; 
}