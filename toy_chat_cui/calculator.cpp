#include <iostream>
#include "calculator.h"

int calculator::plus(int var1, int var2)
{
    std::cout << var1 + var2 << std::endl;

    return var1 + var2;
}

int calculator::minus(int var1, int var2)
{
    std::cout << var1 - var2 << std::endl;

    return var1 - var2;
}

int calculator::divide(int var1, int var2)
{
    std::cout << var1 / var2 << std::endl;

    return var1 / var2;
}

int calculator::multiply(int var1, int var2)
{
    std::cout << var1 * var2 << std::endl;

    return var1 * var2;
}