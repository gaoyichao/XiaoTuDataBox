#ifndef BINARYTREEBASE_HPP
#define BINARYTREEBASE_HPP

#include <BinaryTreeNode.hpp>
#include <BinaryTreeIterator.hpp>
#include <DataQueue.hpp>
#include <iostream>
/*
 * BinaryTree - 二叉树
 */
template <class T>
class BinaryTreeBase {
    public:
        typedef BinaryTreeIteratorBase<T> IteratorBase;
        typedef BinaryTreePreOrderIterator<T> PreOrderIterator;
        typedef BinaryTreeInOrderIterator<T> InOrderIterator;
        typedef BinaryTreePostOrderIterator<T> PostOrderIterator;
        typedef BinaryTreePreOrderIterator<T> DepthFirstIterator;
        typedef BinaryTreeBreadthFirstIterator<T> BreadthFirstIterator;

        friend IteratorBase;
        friend PreOrderIterator;
        friend InOrderIterator;
        friend PostOrderIterator;
        //friend DepthFirstIterator;
        friend BreadthFirstIterator;
    public:
        BinaryTreeBase() : mRoot(NULL) { }
        BinaryTreeBase(BinaryTreeNode<T> *root) : mRoot(root) { }
    public:
        /*
         * minimum - 获取树中的最小节点(最左节点)
         */
        BinaryTreeNode<T> * minimum() {
            if (NULL == mRoot)
                return NULL;

            return mRoot->subtree_min_node();
        }
        /*
         * maxmum - 获取树中的最大节点(最右节点)
         */
        BinaryTreeNode<T> * maximum() {
            if (NULL == mRoot)
                return NULL;

            return mRoot->subtree_max_node();
        }
        /*
         * replace_subtree - 用@v替换@u
         *
         * 该函数返回之后,v替代了u在二叉树中的位置;
         * 仍然保持u的parent指针不变,用于记录u原来的位置,使用者需要根据需要管理parent指针
         *
         * @u: 被替换的节点, 使用者需要保证它是mRoot的后代
         * @v: 将要替换的子树根节点
         */
        bool replace_subtree(BinaryTreeNode<T> *u, BinaryTreeNode<T> *v) {
            if (NULL == u)
                return false;

            if (NULL == u->p && NULL != this->mRoot)
                this->mRoot = v;
            else if (u == u->p->l)
                u->p->l = v;
            else
                u->p->r = v;

            if (NULL != v)
                v->p = u->p;

            return true;
        }

    public:
        BinaryTreeNode<T> * root_ptr() { return mRoot; }
        BinaryTreeNode<T> const * root_ptr() const { return mRoot; }
        bool empty() const { return NULL == this->mRoot; }
    protected:
        BinaryTreeNode<T> *mRoot;
};

#endif

