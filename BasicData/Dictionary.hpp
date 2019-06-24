#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <DictionaryNode.hpp>

template <class KeyType, class ValueType>
class Dictionary {
    public:
        Dictionary() { root.depth = -1; }
        
        DictionaryNode<KeyType, ValueType> * insert(KeyType const * buf, int len) {
            DictionaryNode<KeyType, ValueType> *pNode = &root;

            for (int i = 0; i < len; i++) {
                pNode = pNode->add_child(buf[i]);
            }

            return pNode;
        }

        DictionaryNode<KeyType, ValueType> * find(KeyType const * buf, int len) {
            DictionaryNode<KeyType, ValueType> *pNode = &root;

            for (int i = 0; i < len; i++) {
                pNode = pNode->find_child(buf[i]);
                if (NULL == pNode)
                    return NULL;
            }

            return pNode;
        }
        
        bool remove(KeyType const * buf, int len) {
            DictionaryNode<KeyType, ValueType> *pNode = find(buf, len);

            if (NULL == pNode || pNode->num_children() > 0)
                return false;

            DictionaryNode<KeyType, ValueType> *p = pNode->p;
            for (; 0 < len; len--) {
                p->remove_child(pNode->key);
                pNode = p;
                p = pNode->p;
            }

            return true;
        }

    private:
        DictionaryNode<KeyType, ValueType> root;
};

#endif

