#include <gtest/gtest.h>

#include <locale>
#include <cmath>
#include <GMatrix.hpp>

class DoubleIsZeroEdge {
    public:
        bool operator() (double const & v) const
        {
            return std::isnan(v);
        }
};

class DoubleFillZeroEdge {
    public:
        void operator() (double & v)
        {
            v = std::nan("");
        }
};

TEST(GMatrix, init)
{
    int no = 10;

    GMatrix<double, double, DoubleFillZeroEdge, DoubleIsZeroEdge> *gmatrix = new GMatrix<double, double, DoubleFillZeroEdge, DoubleIsZeroEdge>(no);
    EXPECT_EQ(no, gmatrix->num_nodes());
    EXPECT_EQ(0, gmatrix->num_edges());

    std::cout << *gmatrix << std::endl;

    std::cout << std::numeric_limits<double>::min() << std::endl;
    double na = std::nan("");
    bool isna = (na == std::nan(""));
    unsigned long long *pna = (unsigned long long*)&na;
    std::cout << na << std::endl;
    std::cout << std::hex << *pna << std::dec << std::endl;
    std::cout << (isna ? "yes" : "no") << std::endl;

    DoubleIsZeroEdge dze;
    isna = dze(na);
    std::cout << (isna ? "yes" : "no") << std::endl;

    delete gmatrix;
}


TEST(GMatrix, add_remove_swap)
{
    GMatrix<double, double, DoubleFillZeroEdge, DoubleIsZeroEdge> *gmatrix = new GMatrix<double, double, DoubleFillZeroEdge, DoubleIsZeroEdge>();
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

