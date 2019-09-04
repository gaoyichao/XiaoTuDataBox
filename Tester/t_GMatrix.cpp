#include <gtest/gtest.h>

#include <locale>
#include <cmath>
#include <GMatrix.hpp>

class DoubleIsZeroEdge {
    public:
        bool operator() (double const & v)
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
