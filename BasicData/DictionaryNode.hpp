#ifndef DICTIONARYNODE_HPP
#define DICTIONARYNODE_HPP

#include <RBTree.hpp>
#include <iostream>

template <class KeyType, class ValueType>
class DicBase;

template <class KeyType>
class DicNodeBase {
    public:
        DicNodeBase() : depth(0), p(NULL) {}
        DicNodeBase(KeyType const & data) : depth(0), p(NULL), key(data) {}
        DicNodeBase(DicNodeBase const &node) : depth(0), p(NULL), key(node.key) {}
    private:
        DicNodeBase & operator = (DicNodeBase const &node) { key = node.key; }

    public:
        DicNodeBase * add_child(DicNodeBase * node) {
            if (NULL == node)
                return NULL;

            RBTreeNode<DicNodeBase*> *rbnode = children.find(node->key);

            if (NULL == rbnode) {
                rbnode = children.insert(node);
                rbnode->key->depth = depth+1;
                rbnode->key->p = this;
                return node;
            } else {
                return NULL;
            }
        }

        DicNodeBase * find_child(KeyType const & data) {
            RBTreeNode<DicNodeBase*> *rbnode = children.find(data);

            if (NULL == rbnode)
                return NULL;

            return rbnode->key;
        }

        bool remove_child(KeyType const & data) {
            RBTreeNode<DicNodeBase*> *rbnode = children.find(data);

            if (NULL == rbnode || !rbnode->key->children.empty())
                return false;

            children.remove(rbnode);
            return true;
        }

        int trace_back(KeyType *buf, int len) const {
            DicNodeBase const *pNode = this;

            len = (depth < len) ? depth : len;
            int re = len;

            for (; 0 <= len; len--) {
                buf[len] = pNode->key;
                pNode = pNode->p;
            }

            return re;
        }

        int num_children() const { return children.size(); }

    public:
        DicNodeBase & operator = (KeyType const &data) {
            key = data;
            return *this;
        }

        & operator KeyType() { return key; }
        & operator const KeyType() const { return key; }

    public:
        KeyType key;
        int depth;
        DicNodeBase *p;
        RBTree<DicNodeBase*> children; 
};

template <class KeyType, class ValueType>
class DicEndNode : public DicNodeBase<KeyType> {
    public:
        DicEndNode(KeyType const & k, ValueType const & v) : DicNodeBase<KeyType>(k), value(v) {}
        ValueType value; 
};

#endif

