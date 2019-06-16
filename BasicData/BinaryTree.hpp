#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <BinaryTreeNode.hpp>
#include <DataQueue.hpp>
/*
 * BinaryTree - 二叉树
 */
template <class T>
class BinaryTree {
    public:
        BinaryTree() : mRoot(NULL), mIsSearchTree(true) { }
        BinaryTree(BinaryTreeNode<T> *root) : mRoot(root) {
            mIsSearchTree = (NULL == root) ? true : false;
        }
        ~BinaryTree() {
            if (!mIsSearchTree)
                return;
            BinaryTreeNode<double> * node;
            if (NULL != mRoot) {
                for (node = postorder_traversal(); NULL != node; node = postorder_traversal()) {
                    delete node;
                }
            }
        }
    public:
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

            if (NULL == u->p && NULL != mRoot)
                mRoot = v;
            else if (u == u->p->l)
                u->p->l = v;
            else
                u->p->r = v;

            if (NULL != v)
                v->p = u->p;

            return true;
        }
    public:
        bool empty() const { return NULL == mRoot; }
        bool is_search_tree() const { return mIsSearchTree; }
    public:
        /*
         * preorder_traversal - 先序遍历二叉树,每次只返回一个元素
         */
        BinaryTreeNode<T> *preorder_traversal() {
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
            BinaryTreeNode<T> *re, *tmp;
            int size = mPostOrderQueue.size();

            if (0 == size) {
                mPostOrderQueue.push_back(mRoot);
                mPostOrderQueue.push_back(mRoot);
            }

            mPostOrderQueue.pop_back(re);
            if (NULL == re)
                return NULL;
            if (0 == mPostOrderQueue.size())
                mPostOrderQueue.push_back(NULL);
            mPostOrderQueue.peek_back(tmp);

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
                mPostOrderQueue.peek_back(tmp);
            }

            return re;
        }

    public:
        /*****************************************************************
                    二叉搜索树相关成员
         *****************************************************************/
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
    protected:
        void insert(BinaryTreeNode<T> * z) {
            BinaryTreeNode<T> *y = NULL;
            BinaryTreeNode<T> *x = mRoot;

            while (NULL != x) {
                y = x;
                if (z->key < x->key)
                    x = x->l;
                else
                    x = x->r;
            }

            z->p = y;
            if (NULL == y)
                mRoot = z;
            else if (z->key < y->key)
                y->l = z;
            else
                y->r = z;
        }
    public:
        /*
         * insert - 二叉搜索树插入元素
         *
         * @data: 插入元素
         */
        BinaryTreeNode<T> * insert(T const & data) {
            if (!mIsSearchTree)
                return NULL;

            BinaryTreeNode<T> *re = new BinaryTreeNode<T>(data);
            insert(re);

            return re;
        }
        /*
         * find - 二叉搜索树查找元素
         *
         * @data: 目标元素
         */
        BinaryTreeNode<T> * find(T const & data) {
            BinaryTreeNode<T> * re = mRoot;

            while (NULL != re) {
                if (data < re->key)
                    re = re->l;
                else if (data > re->key)
                    re = re->r;
                else
                    break;
            }

            return re;
        }
        /*
         * remove - 二叉搜索树删除节点
         *
         * @node: 目标节点,需要使用者保证其是本树的节点
         */
        void remove(BinaryTreeNode<T> * node) {
            if (NULL == node)
                return;

            if (NULL == node->l)
                replace_subtree(node, node->r);
            else if (NULL == node->r)
                replace_subtree(node, node->l);
            else {
                BinaryTreeNode<T> *n = node->r->subtree_min_node();
                if (node != n->p) {
                    replace_subtree(n, n->r);
                    n->r = node->r;
                    n->r->p = n;
                }

                replace_subtree(node, n);
                n->l = node->l;
                n->l->p = n;
            }

            if (mIsSearchTree)
                delete node;
        }
        /*
         * remove - 二叉搜索树删除元素
         *
         * @node: 目标元素
         */
        void remove(T const & data) { remove(find(data)); }

    public:
        BinaryTreeNode<T> * root_ptr() { return mRoot; }
        BinaryTreeNode<T> const * root_ptr() const { return mRoot; }
    protected:
        bool mIsSearchTree;
        BinaryTreeNode<T> *mRoot;
        DataQueue<BinaryTreeNode<T> *> mPreOrderQueue;
        DataQueue<BinaryTreeNode<T> *> mInOrderQueue;
        DataQueue<BinaryTreeNode<T> *> mPostOrderQueue;
};


#endif
