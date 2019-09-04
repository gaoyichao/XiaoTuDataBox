#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <DictionaryNode.hpp>
#include <DictionaryIterator.hpp>

template <class KeyType, class ValueType>
class DicBase {
    public:
        typedef DicNodeBase<KeyType> NodeType;
        typedef DicEndNode<KeyType, ValueType> EndNodeType;
 
        typedef DicIteratorBase<KeyType, ValueType> IteratorBase;
        typedef DicPreOrderIterator<KeyType, ValueType> PreOrderIterator;
        typedef DicPostOrderIterator<KeyType, ValueType> PostOrderIterator;
        typedef DicPreOrderIterator<KeyType, ValueType> DepthFirstIterator;
        typedef DicBreadthFirstIterator<KeyType, ValueType> BreadthFirstIterator;

        friend IteratorBase;
        friend PreOrderIterator;
        friend PostOrderIterator;
        //friend DepthFirstIterator;
        friend BreadthFirstIterator;
    public:
        DicBase() { mRoot.depth = -1; }

         ~DicBase() {
            DicPreOrderIterator<KeyType, ValueType> it(*this);
            ++it;
            for (; NULL != it; ++it) {
                delete it.ptr();
            }
        }

       
        EndNodeType * insert(ValueType const & value, KeyType const * buf, int len, KeyType const & zeroKey) {
            NodeType *pNode = &mRoot;

            for (int i = 0; i < len; i++)
                pNode = pNode->add_child(new NodeType(buf[i]));

            return (EndNodeType*)pNode->add_child(new EndNodeType(zeroKey, value));
        }

        EndNodeType * find(KeyType const * buf, int len, KeyType const & zeroKey) {
            NodeType *pNode = &mRoot;

            for (int i = 0; i < len; i++) {
                pNode = pNode->find_child(buf[i]);
                if (NULL == pNode)
                    return NULL;
            }
            return (EndNodeType*)pNode->find_child(zeroKey);
        }
        
        bool remove(KeyType const * buf, int len, KeyType const & zeroKey) {
            NodeType *pNode = find(buf, len, zeroKey);
            if (NULL == pNode || pNode->num_children() > 0)
                return false;
            NodeType *p = pNode->p;
            while (NULL != p) {
                NodeType *tmp = pNode;
                if (!p->remove_child(pNode->key))
                    break;

                pNode = p;
                p = pNode->p;

                delete tmp;
            }
            return true;
        }

    protected:
        NodeType mRoot;
};

template <class KeyType, class ValueType>
class Dictionary : public DicBase<KeyType, ValueType> {
     public:
        Dictionary() {
            this->mRoot.depth = -1;
        }
};

template <class ValueType>
class Dictionary<char, ValueType> : public DicBase<char, ValueType> {
    public:
        typedef DicNodeBase<char> NodeType;
        typedef DicEndNode<char, ValueType> EndNodeType;
     public:
        Dictionary() {
            this->mRoot.depth = -1;
            this->mRoot.key = 'A';
        }

        EndNodeType * insert(std::string const & str, ValueType const & v) {
            int len = str.size();
            DicBase<char, ValueType> *base = (DicBase<char, ValueType>*)this;
            return base->insert(v, str.c_str(), len, '\0');
        }

        EndNodeType * find(std::string const & str) {
            int len = str.size();
            DicBase<char, ValueType> *base = (DicBase<char, ValueType>*)this;
            return base->find(str.c_str(), len, '\0');
        }

        bool remove(std::string const & str) {
            int len = str.size();
            DicBase<char, ValueType> *base = (DicBase<char, ValueType>*)this;
            return base->remove(str.c_str(), len, '\0');
        }
};

#endif

