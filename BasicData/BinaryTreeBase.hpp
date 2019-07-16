#ifndef BINARYTREEBASE_HPP
#define BINARYTREEBASE_HPP

#include <BinaryTreeNode.hpp>
#include <DataQueue.hpp>
#include <iostream>
/*
 * BinaryTree - 二叉树
 */
template <class T>
class BinaryTreeBase {
    public:
        BinaryTreeBase() : mRoot(NULL) { }
        BinaryTreeBase(BinaryTreeNode<T> *root) : mRoot(root) { }
    public:
        /*
         * preorder_traversal - 先序遍历二叉树,每次只返回一个元素
         */
        BinaryTreeNode<T> *preorder_traversal() {
            if (NULL == mRoot)
                return NULL;

            BinaryTreeNode<T> *re;
            int size = mPreOrderQueue.size();
            
            if (0 == size) {
                re = mRoot;
            } else {
                mPreOrderQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            if (NULL != re->r)
                mPreOrderQueue.push_back(re->r);
            if (NULL != re->l)
                mPreOrderQueue.push_back(re->l);

            if (0 == mPreOrderQueue.size())
                mPreOrderQueue.push_back(NULL);

            return re;
        }
        /*
         * inorder_traversal - 中序遍历二叉树,每次只返回一个元素
         */
        BinaryTreeNode<T> *inorder_traversal() {
            if (NULL == mRoot)
                return NULL;

            BinaryTreeNode<T> *re;
            int size = mInOrderQueue.size();

            if (0 == size) {
                re = mRoot;
                while (NULL != re->l) {
                    mInOrderQueue.push_back(re);
                    re = re->l;
                }
            } else {
                mInOrderQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            if (NULL != re->r) {
                mInOrderQueue.push_back(re->r);
                BinaryTreeNode<T> *root = re->r;
                while (NULL != root->l) {
                    mInOrderQueue.push_back(root->l);
                    root = root->l;
                }
            }

            if (0 == mInOrderQueue.size())
                mInOrderQueue.push_back(NULL);

            return re;
        }
        /*
         * postorder_traversal - 后序遍历,每次只返回一个元素
         */
        BinaryTreeNode<T> *postorder_traversal() {
            if (NULL == mRoot)
                return NULL;

            BinaryTreeNode<T> *re, *tmp;
            int size = mPostOrderQueue.size();

            if (0 == size) {
                mPostOrderQueue.push_back(mRoot);
                mPostOrderQueue.push_back(mRoot);
            }

            mPostOrderQueue.pop_back(re);
            if (NULL == re)
                return NULL;

            if (!mPostOrderQueue.peek_back(tmp))
                mPostOrderQueue.push_back(NULL);


            while (tmp == re) {
                if (NULL != re->r) {
                    mPostOrderQueue.push_back(re->r);
                    mPostOrderQueue.push_back(re->r);
                }

                if (NULL != re->l) {
                    mPostOrderQueue.push_back(re->l);
                    mPostOrderQueue.push_back(re->l);
                }

                mPostOrderQueue.pop_back(re);
                if (!mPostOrderQueue.peek_back(tmp)) {
                    mPostOrderQueue.push_back(NULL);
                    break;
                }
            }

            return re;
        }

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
        DataQueue<BinaryTreeNode<T> *> mPreOrderQueue;
        DataQueue<BinaryTreeNode<T> *> mInOrderQueue;
        DataQueue<BinaryTreeNode<T> *> mPostOrderQueue;
};

#endif

