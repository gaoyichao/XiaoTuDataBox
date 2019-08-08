#include <gtest/gtest.h>
#include <Array2D.hpp>
#include <iostream>


TEST(Array2D, init)
{
    Array2D<3, 3, double> array;

    for (int i = 0; i < array.n(); i++)
        array(i) = 0.1 * i;
    
    std::cout << array << std::endl;
}


