#ifndef GMATRIX_HPP
#define GMATRIX_HPP

#include <iostream>
#include <Array2D.hpp>
#include <DataArray.hpp>

template <class NodeType, class EdgeType>
class GMatrix
{
    public:
        GMatrix() {};

        GMatrix(int no) : nodes(no, 0), m(no, no, NULL) {

        }


        friend std::ostream & operator << (std::ostream & stream, GMatrix const & gm)
        {
            stream << "nodes:" << std::hex << gm.nodes << std::dec << std::endl;;
            stream << std::hex << gm.m << std::dec;
            return stream;
        }


    protected:
        Array2D<EdgeType *> m;
        DataArray<NodeType> nodes;
};


#endif

