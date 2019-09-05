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
            int nv = nodes.size();
            if (i >= nv || j >= nv || IsConnected(i, j))
                return false;
            matrix(i, j) = key;
            return true;
        }

        bool add_node(int i, NodeType const key)
        {
            int nv = nodes.size();
            if (i > nv || 0 != nodes.insert(i, key))
                return false;

            if (!matrix.insert_row(i, 1) || !matrix.insert_column(i, 1))
                return false;

            nv = nodes.size();
            for (int idx = 0; idx < nv; idx++) {
                FillZeroEdge(matrix(idx, i));
                FillZeroEdge(matrix(i, idx));
            }

            return true;
        }

        bool remove_edge(int i, int j)
        {
            int nv = nodes.size();
            if (i >= nv || j >= nv)
                return false;

            FillZeroEdge(matrix(i, j));
            return true;
        }

        bool remove_node(int i)
        {
            int nv = nodes.size();
            if (i > nv || 0 != nodes.remove(i, i+1))
                return false;

            if (!matrix.remove_row(i, 1) || !matrix.remove_column(i, 1))
                return false;
            return true;
        }

        bool swap_nodes(int i, int j)
        {
            int nv = nodes.size();
            if (i >= nv || j >= nv)
                return false;
            if (0 != nodes.swap(i, j))
                return false;
            if (!matrix.swap_row(i, j) || !matrix.swap_column(i, j))
                return false;
            return true;
        }


    protected:
        Array2D<EdgeType> matrix;
        DataArray<NodeType> nodes;

        FillZeroEdgeFunc FillZeroEdge;
        IsZeroEdgeFunc IsZeroEdge;
};


#endif

