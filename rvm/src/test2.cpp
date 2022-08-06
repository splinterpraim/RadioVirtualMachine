
#include "test2.h"


void test_fun()
{
    Car car1;
    struct r one;
    one.first = car1.get_size();

    one.symb = dosmfn(one.first);
    std::cout << one.symb << std::endl;
}

char dosmfn(int a)
{
    if (a == 2)
    {
        return 'g';
    }
    return 'b';
}