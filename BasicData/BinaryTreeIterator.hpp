#ifndef BINARYTREEITERATOR_HPP
#define BINARYTREEITERATOR_HPP

#include <BinaryTreeNode.hpp>
#include <DataQueue.hpp>
#include <iostream>

template <class T>
class BinaryTreeBase;
/*
 * IteratorBase - 遍历器基类
 */
template <class T>
class BinaryTreeIteratorBase {
    typedef BinaryTreeNode<T> NodeType;
    public:
        BinaryTreeIteratorBase(BinaryTreeBase<T> & tree) : mtree(tree) { }
        BinaryTreeIteratorBase(BinaryTreeIteratorBase & it) : mtree(it.mtree) { }

        friend bool operator == (NodeType * ptr, BinaryTreeIteratorBase const & it) { return ptr == it.cur; }
        friend bool operator == (BinaryTreeIteratorBase const & it, NodeType * ptr) { return ptr == it.cur; }
        friend bool operator != (NodeType * ptr, BinaryTreeIteratorBase const & it) { return ptr != it.cur; }
        friend bool operator != (BinaryTreeIteratorBase const & it, NodeType * ptr) { return ptr != it.cur; }

        NodeType * ptr() { return cur; }

        NodeType * operator -> () { return cur; }
        NodeType & operator * () { return *cur; }
    protected:
        NodeType * cur;
        BinaryTreeBase<T> & mtree;
        DataQueue<NodeType*> mQueue;
};

/*
 * PreOrderIterator - 先序遍历器
 */
template <class T>
class BinaryTreePreOrderIterator : public BinaryTreeIteratorBase<T> {
    typedef BinaryTreeIteratorBase<T> IteratorBase;
    typedef BinaryTreeNode<T> NodeType;
    public:
        BinaryTreePreOrderIterator(BinaryTreeBase<T> & tree) : IteratorBase(tree) {
            this->cur = traversal();
        }
        BinaryTreePreOrderIterator(BinaryTreePreOrderIterator & it) : IteratorBase(it) {
            this->cur = traversal();
        }
        
        BinaryTreePreOrderIterator & operator ++ () {
            this->cur = traversal();
            return *this;
        }
    private:
        NodeType * traversal() {
            if (NULL == this->mtree.mRoot)
                return NULL;

            BinaryTreeNode<T> *re;
            int size = this->mQueue.size();
            
            if (0 == size) {
                re = this->mtree.mRoot;
            } else {
                this->mQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            if (NULL != re->r)
                this->mQueue.push_back(re->r);
            if (NULL != re->l)
                this->mQueue.push_back(re->l);

            if (0 == this->mQueue.size())
                this->mQueue.push_back(NULL);

            return re;
        }
};

template <class T>
/*
 * InOrderIterator - 中序遍历器
 */
class BinaryTreeInOrderIterator : public BinaryTreeIteratorBase<T> {
    typedef BinaryTreeIteratorBase<T> IteratorBase;
    typedef BinaryTreeNode<T> NodeType;
    public:
        BinaryTreeInOrderIterator(BinaryTreeBase<T> & tree) : IteratorBase(tree) {
            this->cur = traversal();
        }
        BinaryTreeInOrderIterator(BinaryTreeInOrderIterator & it) : IteratorBase(it) {
            this->cur = traversal();
        }
        
        BinaryTreeInOrderIterator & operator ++ () {
            this->cur = traversal();
            return *this;
        }
    private:
        NodeType * traversal() {
            if (NULL == this->mtree.mRoot)
                return NULL;

            BinaryTreeNode<T> *re;
            int size = this->mQueue.size();

            if (0 == size) {
                re = this->mtree.mRoot;
                while (NULL != re->l) {
                    this->mQueue.push_back(re);
                    re = re->l;
                }
            } else {
                this->mQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            if (NULL != re->r) {
                this->mQueue.push_back(re->r);
                BinaryTreeNode<T> *root = re->r;
                while (NULL != root->l) {
                    this->mQueue.push_back(root->l);
                    root = root->l;
                }
            }

            if (0 == this->mQueue.size())
                this->mQueue.push_back(NULL);

            return re;
        }
};

/*
 * PostOrderIterator - 后序遍历器
 */
template <class T>
class BinaryTreePostOrderIterator : public BinaryTreeIteratorBase<T> {
    typedef BinaryTreeIteratorBase<T> IteratorBase;
    typedef BinaryTreeNode<T> NodeType;
    public:
        BinaryTreePostOrderIterator(BinaryTreeBase<T> & tree) : IteratorBase(tree) {
            this->cur = traversal();
        }
        BinaryTreePostOrderIterator(BinaryTreePostOrderIterator & it) : IteratorBase(it) {
            this->cur = traversal();
        }
        
        BinaryTreePostOrderIterator & operator ++ () {
            this->cur = traversal();
            return *this;
        }
    private:
        NodeType * traversal() {
            if (NULL == this->mtree.mRoot)
                return NULL;

            BinaryTreeNode<T> *re, *tmp;
            int size = this->mQueue.size();

            if (0 == size) {
                this->mQueue.push_back(this->mtree.mRoot);
                this->mQueue.push_back(this->mtree.mRoot);
            }

            this->mQueue.pop_back(re);
            if (NULL == re)
                return NULL;

            if (!this->mQueue.peek_back(tmp))
                this->mQueue.push_back(NULL);


            while (tmp == re) {
                if (NULL != re->r) {
                    this->mQueue.push_back(re->r);
                    this->mQueue.push_back(re->r);
                }

                if (NULL != re->l) {
                    this->mQueue.push_back(re->l);
                    this->mQueue.push_back(re->l);
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
template <class T>
class BinaryTreeBreadthFirstIterator : public BinaryTreeIteratorBase<T> {
    typedef BinaryTreeIteratorBase<T> IteratorBase;
    typedef BinaryTreeNode<T> NodeType;
    public:
        BinaryTreeBreadthFirstIterator(BinaryTreeBase<T> & tree) : IteratorBase(tree) {
            this->cur = traversal();
        }
        BinaryTreeBreadthFirstIterator(BinaryTreeBreadthFirstIterator & it) : IteratorBase(it) {
            this->cur = traversal();
        }
        
        BinaryTreeBreadthFirstIterator & operator ++ () {
            this->cur = traversal();
            return *this;
        }

    private:
        NodeType * traversal() {
            if (NULL == this->mtree.mRoot)
                return NULL;

            NodeType * re;
            int size = this->mQueue.size();

            if (0 == size) {
                re = this->mtree.mRoot;
            } else {
                this->mQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            if (NULL != re->l)
                this->mQueue.push_front(re->l);
            if (NULL != re->r)
                this->mQueue.push_front(re->r);

            if (0 == this->mQueue.size())
                this->mQueue.push_front(NULL);

            return re;
        }
};


#endif

