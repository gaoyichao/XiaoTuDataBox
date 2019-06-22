#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <GNode.hpp>
#include <GEdge.hpp>

#include <DataArray.hpp>

template <class NodeType, class EdgeType>
class Graph {
    public:
        Graph() {};

        Graph(int no) : nodes(no) {
            for (int i = 0; i < no; i++)
                nodes[i] = new GNode<NodeType, EdgeType>;
        }

        ~Graph() {
            int no = nodes.size();
            int ne = edges.size();

            for (int i = 0; i < no; i++)
                delete nodes[i];
            for (int i = 0; i < ne; i++)
                delete edges[i];
        }
    public:
        GNode<NodeType, EdgeType> *add_node(NodeType const & key) {
            GNode<NodeType, EdgeType> *re = new GNode<NodeType, EdgeType>(key);
            nodes.push(re);
            return re;
        }

        GEdge<NodeType, EdgeType> *add_edge(GNode<NodeType, EdgeType> *from, GNode<NodeType, EdgeType> *to, EdgeType const & key) {
            if (NULL == nodes.find(from))
                return NULL;
            if (NULL == nodes.find(to))
                return NULL;

            GEdge<NodeType, EdgeType> *edge = new GEdge<NodeType, EdgeType>(from, to, key);
            from->add_outedge(edge);
            to->add_inedge(edge);
            edges.push(edge);

            return edge;
        }

    public:
        int num_nodes() const { return nodes.size(); }
        int num_edges() const { return edges.size(); }

    public:
        DataArray<GNode<NodeType, EdgeType> *> nodes;
        DataArray<GEdge<NodeType, EdgeType> *> edges;
};

#endif

