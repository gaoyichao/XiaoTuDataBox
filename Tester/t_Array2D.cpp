#include <gtest/gtest.h>
#include <Array2D.hpp>
#include <iostream>


TEST(Array2D, init)
{
    Array2D<double> *array = new Array2D<double>(3, 3);

    for (int i = 0; i < array->size(); i++)
        (*array)(i) = 0.1 * i;
    
    EXPECT_EQ(9, array->size());
    std::cout << *array << std::endl;

    delete array;

    array = new Array2D<double>(3, 3, 1.41421);
    std::cout << *array << std::endl;

    delete array;
}


