#include <gtest/gtest.h>
#include <Array2D.hpp>
#include <iostream>


TEST(Array2D, init)
{
    Array2D<double> *array = new Array2D<double>(3, 3);

    for (int i = 0; i < array->size(); i++)
        (*array)(i) = 0.1 * i;
    
    EXPECT_EQ(9, array->size());

    delete array;

    array = new Array2D<double>(3, 3, 1.41421);
    EXPECT_EQ(9, array->size());

    delete array;

    array = new Array2D<double>(0, 3);
    EXPECT_EQ(0, array->size());
    EXPECT_EQ(0, array->num_rows());
    EXPECT_EQ(3, array->num_cols());

    delete array;
}

TEST(Array2D, swap)
{
    Array2D<double> *array = new Array2D<double>(3, 3);

    for (int i = 0; i < array->size(); i++)
        (*array)(i) = 0.1 * i;
    EXPECT_EQ(9, array->size());
    std::cout << *array << std::endl;

    array->swap_row(0, 2);
    std::cout << *array << std::endl;

    array->swap_column(0, 2);
    std::cout << *array << std::endl;

    delete array;
}



TEST(Array2D, insert)
{
    Array2D<double> *array = new Array2D<double>(3, 3);

    for (int i = 0; i < array->size(); i++)
        (*array)(i) = 0.1 * i;
    EXPECT_EQ(9, array->size());

    EXPECT_TRUE(array->insert_row(2, 1, 1.41421));
    EXPECT_EQ(12, array->size());
    EXPECT_EQ(4, array->num_rows());
    EXPECT_EQ(3, array->num_cols());

    EXPECT_TRUE(array->insert_row(0, 2, 1.2));
    EXPECT_EQ(18, array->size());
    EXPECT_EQ(6, array->num_rows());
    EXPECT_EQ(3, array->num_cols());

    EXPECT_FALSE(array->insert_row(7, 3, 1.2));
    EXPECT_EQ(18, array->size());
    EXPECT_EQ(6, array->num_rows());
    EXPECT_EQ(3, array->num_cols());

    EXPECT_TRUE(array->insert_row(6, 3, 1.2));
    EXPECT_EQ(27, array->size());
    EXPECT_EQ(9, array->num_rows());
    EXPECT_EQ(3, array->num_cols());

    EXPECT_TRUE(array->insert_column(3, 1));
    EXPECT_EQ(36, array->size());
    EXPECT_EQ(9, array->num_rows());
    EXPECT_EQ(4, array->num_cols());

    EXPECT_TRUE(array->insert_column(0, 2, 1.1));
    EXPECT_EQ(54, array->size());
    EXPECT_EQ(9, array->num_rows());
    EXPECT_EQ(6, array->num_cols());

    EXPECT_FALSE(array->insert_column(7, 3, 9.1));
    EXPECT_EQ(54, array->size());
    EXPECT_EQ(9, array->num_rows());
    EXPECT_EQ(6, array->num_cols());

    EXPECT_TRUE(array->insert_column(6, 3, 9.1));
    EXPECT_EQ(81, array->size());
    EXPECT_EQ(9, array->num_rows());
    EXPECT_EQ(9, array->num_cols());
    delete array;

    array = new Array2D<double>(0, 4);
    EXPECT_EQ(0, array->size());
    EXPECT_EQ(0, array->num_rows());
    EXPECT_EQ(4, array->num_cols());

    EXPECT_FALSE(array->insert_row(1, 1));
    EXPECT_TRUE(array->insert_row(0, 1, 3.3));
    EXPECT_EQ(4, array->size());
    EXPECT_EQ(1, array->num_rows());
    EXPECT_EQ(4, array->num_cols());
    delete array;

    array = new Array2D<double>(4, 0);
    EXPECT_EQ(0, array->size());
    EXPECT_EQ(4, array->num_rows());
    EXPECT_EQ(0, array->num_cols());

    EXPECT_FALSE(array->insert_column(1, 1));
    EXPECT_TRUE(array->insert_column(0, 1, 3.3));
    EXPECT_EQ(4, array->size());
    EXPECT_EQ(4, array->num_rows());
    EXPECT_EQ(1, array->num_cols());
    delete array;

    array = new Array2D<double>(0, 0);
    EXPECT_EQ(0, array->size());
    EXPECT_EQ(0, array->num_rows());
    EXPECT_EQ(0, array->num_cols());

    EXPECT_FALSE(array->insert_row(1, 1));
    EXPECT_FALSE(array->insert_column(1, 1));
    EXPECT_EQ(0, array->size());
    EXPECT_EQ(0, array->num_rows());
    EXPECT_EQ(0, array->num_cols());

    EXPECT_TRUE(array->insert_row(0, 1, 3.3));
    EXPECT_EQ(0, array->size());
    EXPECT_EQ(1, array->num_rows());
    EXPECT_EQ(0, array->num_cols());

    EXPECT_TRUE(array->insert_column(0, 1, 3.3));
    EXPECT_EQ(1, array->size());
    EXPECT_EQ(1, array->num_rows());
    EXPECT_EQ(1, array->num_cols());

    EXPECT_TRUE(array->insert_row(0, 1, 2.3));
    EXPECT_EQ(2, array->size());
    EXPECT_EQ(2, array->num_rows());
    EXPECT_EQ(1, array->num_cols());

    EXPECT_TRUE(array->insert_column(0, 1, 2.3));
    EXPECT_EQ(4, array->size());
    EXPECT_EQ(2, array->num_rows());
    EXPECT_EQ(2, array->num_cols());
    delete array;
}


TEST(Array2D, remove)
{
    Array2D<double> *array = new Array2D<double>(3, 3);
    for (int i = 0; i < array->size(); i++)
        (*array)(i) = 0.1 * i;
    EXPECT_EQ(9, array->size());

    EXPECT_FALSE(array->remove_row(3, 1));
    EXPECT_EQ(9, array->size());

    EXPECT_FALSE(array->remove_row(2, 2));
    EXPECT_EQ(9, array->size());

    EXPECT_TRUE(array->remove_row(2, 1));
    EXPECT_EQ(6, array->size());

    EXPECT_TRUE(array->remove_row(0, 2));
    EXPECT_EQ(0, array->size());

    EXPECT_FALSE(array->remove_row(0, 1));
    delete array;

    array = new Array2D<double>(3, 3);
    for (int i = 0; i < array->size(); i++)
        (*array)(i) = 0.1 * i;
    EXPECT_EQ(9, array->size());

    EXPECT_FALSE(array->remove_column(3, 1));
    EXPECT_EQ(9, array->size());

    EXPECT_FALSE(array->remove_column(2, 2));
    EXPECT_EQ(9, array->size());

    EXPECT_TRUE(array->remove_column(2, 1));
    EXPECT_EQ(6, array->size());

    EXPECT_TRUE(array->remove_column(0, 2));
    EXPECT_EQ(0, array->size());

    EXPECT_FALSE(array->remove_column(0, 1));
    delete array;
}

