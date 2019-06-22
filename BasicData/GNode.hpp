#ifndef GNODE_HPP
#define GNODE_HPP

#include <DataArray.hpp>

template <class NodeType, class EdgeType> class GEdge;
template <class NodeType, class EdgeType> class Graph;

template <class NodeType, class EdgeType>
class GNode {
    friend class GEdge<NodeType, EdgeType>;

    public:
        GNode() { }
        GNode(NodeType const & data) : key(data) { }

    public:
        bool add_inedge(GEdge<NodeType, EdgeType> * edge) {
            if (NULL == edge || NULL == edge->from || this != edge->to)
                return false;

            mInEdges.push(edge);
            return true;
        }
        bool add_outedge(GEdge<NodeType, EdgeType> * edge) {
            if (NULL == edge || NULL == edge->to || this != edge->from)
                return false;
            mOutEdges.push(edge);
        }
    public:
        int degree_out() const { return mOutEdges.size(); }
        int degree_in() const { return mInEdges.size(); }
    public:
        GNode & operator = (NodeType const &data) {
            key = data;
            return *this;
        }
        & operator NodeType() { return key; }
        & operator const NodeType() const { return key; }

    public:
        NodeType key;
    private:
        DataArray<GEdge<NodeType, EdgeType> *> mInEdges;
        DataArray<GEdge<NodeType, EdgeType> *> mOutEdges;
};

#endif

