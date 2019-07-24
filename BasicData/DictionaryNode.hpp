#ifndef DICTIONARYNODE_HPP
#define DICTIONARYNODE_HPP

#include <RBTree.hpp>
#include <iostream>

template <class KeyType, class ValueType> class Dictionary;

template <class KeyType, class ValueType>
class DictionaryNode {
    friend class Dictionary<KeyType, ValueType>;
    public:
        DictionaryNode() : depth(0), p(NULL) {}
        DictionaryNode(KeyType const & data) : depth(0), p(NULL), key(data) {}
        DictionaryNode(DictionaryNode const &node) : depth(0), p(NULL), key(node.key) {}
        ~DictionaryNode() {
        }
    private:
        DictionaryNode & operator = (DictionaryNode const &node) { key = node.key; }

    public:
        DictionaryNode * add_child(DictionaryNode * node) {
            if (NULL == node)
                return NULL;

            RBTreeNode<DictionaryNode*> *rbnode = children.find(node->key);

            if (NULL == rbnode) {
                rbnode = children.insert(node);
                rbnode->key->depth = depth+1;
                rbnode->key->p = this;
                return node;
            } else {
                return NULL;
            }
        }

        DictionaryNode * find_child(KeyType const & data) {
            RBTreeNode<DictionaryNode*> *rbnode = children.find(data);

            if (NULL == rbnode)
                return NULL;

            return rbnode->key;
        }

        bool remove_child(KeyType const & data) {
            RBTreeNode<DictionaryNode*> *rbnode = children.find(data);

            if (NULL == rbnode || !rbnode->key->children.empty())
                return false;

            children.remove(rbnode);
            return true;
        }

        int trace_back(KeyType *buf, int len) const {
            DictionaryNode const *pNode = this;

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
        DictionaryNode & operator = (KeyType const &data) {
            key = data;
            return *this;
        }

        & operator KeyType() { return key; }
        & operator const KeyType() const { return key; }

    public:
        KeyType key;
        ValueType value;
        int depth;
        DictionaryNode *p;
    protected:
        RBTree<DictionaryNode*> children; 
};


#endif

