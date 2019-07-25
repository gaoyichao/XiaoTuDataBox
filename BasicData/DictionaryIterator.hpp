#ifndef DICTIONARYITERATOR_HPP
#define DICTIONARYITERATOR_HPP

#include <DictionaryNode.hpp>

template <class KeyType, class ValueType>
class DicBase;

/*
 * IteratorBase - 遍历器基类
 */
template <class KeyType, class ValueType>
class DicIteratorBase {
    typedef DicNodeBase<KeyType> NodeType;
    public:
        DicIteratorBase(DicBase<KeyType, ValueType> & dic) : mDic(dic) {}
        DicIteratorBase(DicIteratorBase & it) : mDic(it.mDic) {}

        friend bool operator == (NodeType * ptr, DicIteratorBase const & it) { return ptr == it.cur; }
        friend bool operator == (DicIteratorBase const & it, NodeType * ptr) { return ptr == it.cur; }
        friend bool operator != (NodeType * ptr, DicIteratorBase const & it) { return ptr != it.cur; }
        friend bool operator != (DicIteratorBase const & it, NodeType * ptr) { return ptr != it.cur; }

        NodeType * ptr() { return cur; }

        NodeType * operator -> () { return cur; }
        NodeType & operator * () { return *cur; }
    protected:
        NodeType *cur;
        DicBase<KeyType, ValueType> & mDic;
        DataQueue<NodeType*> mQueue;
};

/*
 * PreOrderIterator - 先序遍历器
 */
template <class KeyType, class ValueType>
class DicPreOrderIterator : public DicIteratorBase<KeyType, ValueType> {
    typedef DicIteratorBase<KeyType, ValueType> IteratorBase;
    typedef DicNodeBase<KeyType> NodeType;
    public:
        DicPreOrderIterator(DicBase<KeyType, ValueType> & dic) : IteratorBase(dic) {
            this->cur = traversal();
        }
        DicPreOrderIterator(DicPreOrderIterator & it) : IteratorBase(it) {
            this->cur = traversal();
        }
        
        DicPreOrderIterator & operator ++ () {
            this->cur = traversal();
            return *this;
        }
    private:
        NodeType * traversal() {
            NodeType *re;
            int size = this->mQueue.size();
            
            if (0 == size) {
                re = &(this->mDic.mRoot);
            } else {
                this->mQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            for (BinaryTreeInOrderIterator<NodeType*> it(re->children); NULL != it; ++it)
                this->mQueue.push_back(*it);

            if (0 == this->mQueue.size())
                this->mQueue.push_back(NULL);

            return re;
        }
};

/*
 * PostOrderIterator - 后序遍历器
 */
template <class KeyType, class ValueType>
class DicPostOrderIterator : public DicIteratorBase<KeyType, ValueType> {
    typedef DicIteratorBase<KeyType, ValueType> IteratorBase;
    typedef DicNodeBase<KeyType> NodeType;
    public:
        DicPostOrderIterator(DicBase<KeyType, ValueType> & dic) : IteratorBase(dic) {
            this->cur = traversal();
        }
        DicPostOrderIterator(DicPostOrderIterator & it) : IteratorBase(it) {
            this->cur = traversal();
        }
        
        DicPostOrderIterator & operator ++ () {
            this->cur = traversal();
            return *this;
        }
    private:
        NodeType * traversal() {
            NodeType *re, *tmp;
            int size = this->mQueue.size();

            if (0 == size) {
                this->mQueue.push_back(&(this->mDic.mRoot));
                this->mQueue.push_back(&(this->mDic.mRoot));
            }

            this->mQueue.pop_back(re);
            if (NULL == re)
                return NULL;

            if (!this->mQueue.peek_back(tmp))
                this->mQueue.push_back(NULL);

            while (tmp == re) {
                for (BinaryTreeInOrderIterator<NodeType*> it(re->children); NULL != it; ++it) {
                    this->mQueue.push_back(*it);
                    this->mQueue.push_back(*it);
                }

                this->mQueue.pop_back(re);
                if (!this->mQueue.peek_back(tmp)) {
                    this->mQueue.push_back(NULL);
                    break;
                }
            }

            return re;
        }
};

/*
 * BreadthFirstIterator - 广度优先遍历器
 */
template <class KeyType, class ValueType>
class DicBreadthFirstIterator : public DicIteratorBase<KeyType, ValueType> {
    typedef DicIteratorBase<KeyType, ValueType> IteratorBase;
    typedef DicNodeBase<KeyType> NodeType;
    public:
        DicBreadthFirstIterator(DicBase<KeyType, ValueType> & dic) : IteratorBase(dic) {
            this->cur = traversal();
        }
        DicBreadthFirstIterator(DicBreadthFirstIterator & it) : IteratorBase(it) {
            this->cur = traversal();
        }
        
        DicBreadthFirstIterator & operator ++ () {
            this->cur = traversal();
            return *this;
        }

    private:
        NodeType * traversal() {
            NodeType * re;
            int size = this->mQueue.size();

            if (0 == size) {
                re = &(this->mDic.mRoot);
            } else {
                this->mQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            for (BinaryTreeInOrderIterator<NodeType*> it(re->children); NULL != it; ++it)
                this->mQueue.push_back(*it);

            if (0 == this->mQueue.size())
                this->mQueue.push_front(NULL);

            return re;
        }
};




#endif

