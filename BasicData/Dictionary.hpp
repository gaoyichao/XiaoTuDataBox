#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <DictionaryNode.hpp>

template <class KeyType, class ValueType>
class Dictionary {
        typedef DictionaryNode<KeyType, ValueType> NodeType;
    public:
        Dictionary() { root.depth = -1; }
        
        NodeType * insert(KeyType const * buf, int len) {
            NodeType *pNode = &root;

            for (int i = 0; i < len; i++)
                pNode = pNode->add_child(new NodeType(buf[i]));

            return pNode;
        }

        NodeType * find(KeyType const * buf, int len) {
            NodeType *pNode = &root;

            for (int i = 0; i < len; i++) {
                pNode = pNode->find_child(buf[i]);
                if (NULL == pNode)
                    return NULL;
            }

            return pNode;
        }
        
        bool remove(KeyType const * buf, int len) {
            NodeType *pNode = find(buf, len);

            if (NULL == pNode || pNode->num_children() > 0)
                return false;

            NodeType *p = pNode->p;
            while (NULL != p) {
                NodeType *tmp = p->remove_child(pNode->key);
                if (NULL == tmp)
                    break;
                pNode = p;
                p = pNode->p;

                delete tmp;
            }

            return true;
        }

    private:
        NodeType root;
        DataQueue<NodeType *> mQueue;
};

template <class ValueType>
class Dictionary<char, ValueType> {
        typedef DictionaryNode<char, ValueType> NodeType;
    public:
        Dictionary() { root.depth = -1; }

        NodeType * insert(std::string const & str) {
            NodeType *pNode = &root;
            int len = str.size();

            for (int i = 0; i < len; i++) {
                pNode = pNode->add_child(new NodeType(str[i]));
            }

            pNode = pNode->add_child(new NodeType('\0'));
            return pNode;
        }

        NodeType * find(std::string const & str) {
            NodeType *pNode = &root;
            int len = str.size();

            for (int i = 0; i < len; i++) {
                pNode = pNode->find_child(str[i]);
                if (NULL == pNode)
                    return NULL;
            }
            pNode = pNode->find_child('\0');
            return pNode;
        }

        bool remove(std::string const & str) {
            NodeType *pNode = find(str);
            if (NULL == pNode)
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

    private:
        NodeType root;
};

#endif

