#include <gtest/gtest.h>

#include <GMatrix.hpp>

TEST(GMatrix, init)
{
    int no = 10;

    GMatrix<double, double> *gmatrix = new GMatrix<double, double>(no);

    std::cout << *gmatrix << std::endl;

    delete gmatrix;
}
