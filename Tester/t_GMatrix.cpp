#include <gtest/gtest.h>

#include <locale>
#include <cmath>
#include <GMatrix.hpp>

TEST(GMatrix, init)
{
    int no = 10;

    GMatrix<double, double> *gmatrix = new GMatrix<double, double>(no);
    EXPECT_EQ(no, gmatrix->num_nodes());
    EXPECT_EQ(0, gmatrix->num_edges());

    std::cout << *gmatrix << std::endl;
    delete gmatrix;
}


TEST(GMatrix, add_remove_swap)
{
    GMatrix<double, double> *gmatrix = new GMatrix<double, double>();
    EXPECT_EQ(0, gmatrix->num_nodes());
    EXPECT_EQ(0, gmatrix->num_edges());
    std::cout << *gmatrix << std::endl;

    EXPECT_TRUE(gmatrix->add_node(0, 1.2));
    EXPECT_EQ(1, gmatrix->num_nodes());
    EXPECT_EQ(0, gmatrix->num_edges());
    EXPECT_TRUE(gmatrix->add_edge(0, 0, 1.2));

    EXPECT_TRUE(gmatrix->add_node(0, 1.9));
    EXPECT_EQ(2, gmatrix->num_nodes());
    EXPECT_EQ(1, gmatrix->num_edges());
    EXPECT_TRUE(gmatrix->add_edge(0, 1, 2.2));
 
    EXPECT_FALSE(gmatrix->add_node(3, 1.9));
    EXPECT_TRUE(gmatrix->add_node(2, 3.9));
    EXPECT_TRUE(gmatrix->add_edge(2, 0, 3.2));
    EXPECT_EQ(3, gmatrix->num_edges());

    std::cout << *gmatrix << std::endl;
    gmatrix->swap_nodes(0, 2);
    std::cout << *gmatrix << std::endl;

    EXPECT_TRUE(gmatrix->remove_edge(0, 0));
    EXPECT_TRUE(gmatrix->remove_edge(0, 1));

    EXPECT_FALSE(gmatrix->remove_node(3));
    EXPECT_EQ(3, gmatrix->num_nodes());
    EXPECT_TRUE(gmatrix->remove_node(2));
    EXPECT_EQ(2, gmatrix->num_nodes());

    std::cout << *gmatrix << std::endl;
    delete gmatrix;
}

