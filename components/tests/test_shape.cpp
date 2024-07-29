#include "../shape.h"

int main()
{
    std::vector<int> dims = {2, 4};
    Shape s1(dims, 2);
    s1.print();

    Shape s2({10, 8}, 2);
    s2.print();

    Shape s3({2, 3, 4}, 3);
    s3.print();

    Shape s4({2, 3, 4, 5}, 4);
    s4.print();

    Shape s5({2, 3, 4, 5, 6}, 5);

    s4 = s1;
    s4.print();

    return 0;
}
