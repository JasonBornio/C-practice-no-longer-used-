#include "../stack.h"

int main()
{
    std::cout<<std::endl<<"ARRAY3::::::::::: "<<std::endl;
    Array array3(2,2,3);
    array3.lin();
    array3.print();
    //array3.print_grad();

    std::cout<<std::endl<<"SPLIT: DIM 0::::::::::"<<std::endl;
    std::vector<Array> arrays = array3.split(0);
    for (int i = 0; i < 2; i++){
        arrays[i].print();
        //arrays[i].print_grad();
    }

    std::cout<<std::endl<<"SPLIT: DIM 1::::::::::"<<std::endl;
    arrays = array3.split(1);
    for (int i = 0; i < 2; i++){
        arrays[i].print();
        //arrays[i].print_grad();
    }

    std::cout<<std::endl<<"SPLIT: DIM 2::::::::::"<<std::endl;
    arrays = array3.split(2);
    for (int i = 0; i < 3; i++){
        arrays[i].print();
        //arrays[i].print_grad();
    }

    std::cout<<std::endl<<"Arrays to be stacked:::"<<std::endl;
    arrays = array3.split(0);
    for (int i = 0; i < 2; i++){
        arrays[i].print();
        //arrays[i].print_grad();
    }

    std::cout<<std::endl<<"STACK: DIM 0::::::::::"<<std::endl;
    Array array3_1 = stack(arrays, 2, 0);
    array3_1.print();

    std::cout<<std::endl<<"STACK: DIM 1::::::::::"<<std::endl;
    array3_1 = stack(arrays, 2, 1);
    array3_1.print();

    std::cout<<std::endl<<"STACK: DIM 2::::::::::"<<std::endl;
    array3_1 = stack(arrays, 2, 2);
    array3_1.print();
    
}