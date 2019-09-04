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

        NodeType & operator () (int i) { return nodes(i); }
        EdgeType & operator () (int i, int j) { return matrix(i, j); }
        bool IsConnected(int i, int j) const { return !IsZeroEdge(matrix(i, j)); }

        int num_nodes() const { return nodes.size(); }
        int num_edges()
        {
            int re = 0;
            int nv = num_nodes();
            for (int i = 0; i < nv; i++)
                for (int j = 0; j < nv; j++)
                    if (IsConnected(i, j))
                        re++;
            return re;
        }

        bool add_edge(int i, int j, EdgeType const key)
        {
            if (IsConnected(i, j))
                return false;

            matrix(i, j) = key;

            return true;
        }

        bool add_node(int i, NodeType const key)
        {
            std::cout << "key: " << key << std::endl;
            if (0 != nodes.insert(i, key)) {
                std::cout << __FUNCTION__ << std::endl;
                return false;
            }

            int nv = nodes.size();
            std::cout << "nv: " << nv << std::endl;

            if (!matrix.insert_row(i, 1))
                return false;

            if (!matrix.insert_column(i, 1))
                return false;

            for (int idx = 0; idx < nv; idx++) {
                FillZeroEdge(matrix(idx, i));
                FillZeroEdge(matrix(i, idx));
            }

            return true;
        }

        bool remove_edge(int i, int j)
        {
            return true;
        }

        bool remove_node(int i)
        {
            return true;
        }


    protected:
        Array2D<EdgeType> matrix;
        DataArray<NodeType> nodes;

        FillZeroEdgeFunc FillZeroEdge;
        IsZeroEdgeFunc IsZeroEdge;
};


#endif

