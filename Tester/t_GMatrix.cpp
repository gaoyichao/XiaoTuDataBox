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


TEST(GMatrix, add)
{
    GMatrix<double, double, DoubleFillZeroEdge, DoubleIsZeroEdge> *gmatrix = new GMatrix<double, double, DoubleFillZeroEdge, DoubleIsZeroEdge>();
    EXPECT_EQ(0, gmatrix->num_nodes());
    EXPECT_EQ(0, gmatrix->num_edges());
    std::cout << *gmatrix << std::endl;

    gmatrix->add_node(0, 1.2);
    EXPECT_EQ(1, gmatrix->num_nodes());
    EXPECT_EQ(0, gmatrix->num_edges());
    std::cout << *gmatrix << std::endl;

    delete gmatrix;
}

