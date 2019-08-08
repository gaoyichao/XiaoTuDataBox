#ifndef GNODE_HPP
#define GNODE_HPP

#include <DataArray.hpp>
#include <iostream>

template <class NodeType, class EdgeType> class GEdge;
template <class NodeType, class EdgeType> class Graph;

template <class NodeType, class EdgeType>
class GNode {
    friend class GEdge<NodeType, EdgeType>;
    friend class Graph<NodeType, EdgeType>;

    public:
        GNode() { }
        GNode(NodeType const & data) : key(data) { }

    public:
        bool add_inedge(GEdge<NodeType, EdgeType> * edge) {
            if (NULL == edge || NULL == edge->from || this != edge->to)
                return false;

            inEdges.push(edge);
            return true;
        }

        bool remove_inedge(GEdge<NodeType, EdgeType> * edge) {
            if (NULL == edge || NULL == edge->from || this != edge->to)
                return false;

            int idx = inEdges.find_idx(edge);
            inEdges.remove(idx);

            return true;
        }

        bool add_outedge(GEdge<NodeType, EdgeType> * edge) {
            if (NULL == edge || NULL == edge->to || this != edge->from)
                return false;
            outEdges.push(edge);
            return true;
        }

        bool remove_outedge(GEdge<NodeType, EdgeType> * edge) {
            if (NULL == edge || NULL == edge->to || this != edge->from)
                return false;

            int idx = outEdges.find_idx(edge);
            outEdges.remove(idx);

            return true;
        }

    public:
        int degree_out() const { return outEdges.size(); }
        int degree_in() const { return inEdges.size(); }
    public:
        GNode & operator = (NodeType const &data) {
            key = data;
            return *this;
        }
        & operator NodeType() { return key; }
        & operator const NodeType() const { return key; }

        friend std::ostream & operator << (std::ostream & stream, GNode const & n) {
            stream << n.key;
            return stream;
        }


    public:
        NodeType key;
        DataArray<GEdge<NodeType, EdgeType> *> inEdges;
        DataArray<GEdge<NodeType, EdgeType> *> outEdges;
};

#endif

