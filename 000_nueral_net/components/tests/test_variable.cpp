#include "../variable.h"

int main()
{
    Variable var1(5.);
    Variable var2(2.);

    var1.print();
    var2.print();

    Variable var3;

    var3 = var1 + var2;
    var3.print();
    
    var3 = var1 - var2;
    var3.print();

    var3 = var1 * var2;
    var3.print();

    var3 = var1 / var2;
    var3.print();
    

    return 0; 
}