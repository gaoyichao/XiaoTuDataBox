#ifndef GRAPHMATRIX_HPP
#define GRAPHMATRIX_HPP

#include <Graph.hpp>
#include <Array2D.hpp>

template <class NodeType, class EdgeType>
class GraphMatrix : Array2D<GEdge<NodeType, EdgeType> *>
{
    public:
        GraphMatrix(Graph<NodeType, EdgeType> & g)
            : graph(g), nodes(g.nodes), edges(g.edges)
        {
            update();
        }

        void update()
        {
            this->resize(nodes.size(), nodes.size(), NULL);
            int n = edges.size();
            for (int i = 0; i < n; i++) {
                int from = nodes.find_idx(edges[i]->from);
                int to = nodes.find_idx(edges[i]->to);
                this->at(from, to) = edges[i];
            }
        }

        friend std::ostream & operator << (std::ostream & stream, GraphMatrix const & gm)
        {
            stream << std::hex << (Array2D<GEdge<NodeType, EdgeType> *>)gm << std::dec;
            return stream;
        }

    private:
        DataArray<GEdge<NodeType, EdgeType> *> & edges;
        DataArray<GNode<NodeType, EdgeType> *> & nodes;
        Graph<NodeType, EdgeType> & graph;
};


#endif

