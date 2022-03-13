#include "radiolib/functions.h"

int radiolib::sum(uint8_t argc, ...)
{
    int result = 0;
    int currParam = 0;

    std::va_list factor;
    va_start(factor, argc);
    for (int i = 0; i < argc - 1; i++)
    {
        currParam = va_arg(factor, int);
        result += currParam;
        std::cout << currParam << " ";
    }
    std::cout << std::endl;
    std::cout << "res = " << result << std::endl;
    int realResult= va_arg(factor, int&);

    va_end(factor);
    return 0;
}
