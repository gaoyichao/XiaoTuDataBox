#ifndef GMATRIX_HPP
#define GMATRIX_HPP

#include <iostream>
#include <Array2D.hpp>
#include <DataArray.hpp>

template <class NodeType, class EdgeType, class FillZeroEdgeFunc, class IsZeroEdgeFunc>
class GMatrix
{
    public:
        GMatrix() {}
        GMatrix(int n) : nodes(n), matrix(n, n)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    FillZeroEdge(matrix(i, j));
        }

        friend std::ostream & operator << (std::ostream & stream, GMatrix const & gm)
        {
            stream << "nodes:" << std::hex << gm.nodes << std::dec << std::endl;
            stream << std::hex << gm.matrix << std::dec;
            return stream;
        }

        EdgeType & operator () (int i, int j) { return matrix(i, j); }

        bool IsConnected(int i, int j) { return !IsZeroEdge(matrix(i, j)); }

    protected:
        Array2D<EdgeType> matrix;
        DataArray<NodeType> nodes;

        FillZeroEdgeFunc FillZeroEdge;
        IsZeroEdgeFunc IsZeroEdge;
};


#endif

