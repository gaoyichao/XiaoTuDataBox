#ifndef GEDGE_HPP
#define GEDGE_HPP

template <class NodeType, class EdgeType> class GNode;
template <class NodeType, class EdgeType> class Graph;

template <class NodeType, class EdgeType>
class GEdge {
    friend class GNode<NodeType, EdgeType>;
    friend class Graph<NodeType, EdgeType>;

    public:
        GEdge()
            : from(NULL), to(NULL) { }
        GEdge(EdgeType const & data)
            : from(NULL), to(NULL), key(data) { }
        GEdge(GNode<NodeType, EdgeType> *f, GNode<NodeType, EdgeType> *t)
            : from(f), to(t) { }
        GEdge(GNode<NodeType, EdgeType> *f, GNode<NodeType, EdgeType> *t, EdgeType const & data)
            : from(f), to(t), key(data) { }

    public:
        GEdge & operator = (NodeType const &data) {
            key = data;
            return *this;
        }
        & operator NodeType() { return key; }
        & operator const NodeType() const { return key; }


    public:
        EdgeType key;
    private:
        GNode<NodeType, EdgeType> *from;
        GNode<NodeType, EdgeType> *to;
};

#endif

