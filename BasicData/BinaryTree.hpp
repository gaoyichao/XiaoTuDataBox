#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <BinaryTreeBase.hpp>


/*
 * BinaryTree - 二叉树
 */
template <class T, bool isSearchTree = true>
class BinaryTree : public BinaryTreeBase<T> {
    public:
        BinaryTree() : BinaryTreeBase<T>() { }
        BinaryTree(BinaryTreeNode<T> *root) : BinaryTreeBase<T>(root) { }
        ~BinaryTree() {
            if (!isSearchTree)
                return;
            BinaryTreeNode<T> * node;
            if (NULL != this->mRoot) {
                for (BinaryTreePostOrderIterator<T> it(*this); NULL != it; ++it) {
                    delete it.ptr();
                }
            }
        }
    public:
        bool is_search_tree() const { return isSearchTree; }

    protected:
        /*****************************************************************
                    二叉搜索树相关成员
         *****************************************************************/
        void insert(BinaryTreeNode<T> * z) {
            BinaryTreeNode<T> *y = NULL;
            BinaryTreeNode<T> *x = this->mRoot;

            while (NULL != x) {
                y = x;
                if (z->key < x->key)
                    x = x->l;
                else
                    x = x->r;
            }

            z->p = y;
            if (NULL == y)
                this->mRoot = z;
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
            if (!isSearchTree)
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
            BinaryTreeNode<T> * re = this->mRoot;

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
                this->replace_subtree(node, node->r);
            else if (NULL == node->r)
                this->replace_subtree(node, node->l);
            else {
                BinaryTreeNode<T> *n = node->r->subtree_min_node();
                if (node != n->p) {
                    this->replace_subtree(n, n->r);
                    n->r = node->r;
                    n->r->p = n;
                }

                this->replace_subtree(node, n);
                n->l = node->l;
                n->l->p = n;
            }

            if (isSearchTree)
                delete node;
        }
        /*
         * remove - 二叉搜索树删除元素
         *
         * @node: 目标元素
         */
        void remove(T const & data) { remove(find(data)); }
};


/*
 * BinaryTree - 二叉树指针类型偏特化
 */
template <class T, bool isSearchTree>
class BinaryTree<T*, isSearchTree> : public BinaryTreeBase<T*> {
    public:
        BinaryTree() : BinaryTreeBase<T*>() {}
        BinaryTree(BinaryTreeNode<T*> *root) : BinaryTreeBase<T*>(root) { }
        ~BinaryTree() {
            if (!isSearchTree)
                return;
            BinaryTreeNode<T*> * node;
            if (NULL != this->mRoot) {
                for (BinaryTreePostOrderIterator<T*> it(*this); NULL != it; ++it) {
                    delete it.ptr();
                }
            }
        }
    public:
        bool is_search_tree() const { return isSearchTree; }
    protected:
        /*****************************************************************
                    二叉搜索树相关成员
         *****************************************************************/
        void insert(BinaryTreeNode<T*> * z) {
            BinaryTreeNode<T*> *y = NULL;
            BinaryTreeNode<T*> *x = this->mRoot;

            while (NULL != x) {
                y = x;
                if ((*(z->key)) < (*(x->key)))
                    x = x->l;
                else
                    x = x->r;
            }

            z->p = y;
            if (NULL == y)
                this->mRoot = z;
            else if ((*(z->key)) < (*(y->key)))
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
        BinaryTreeNode<T*> * insert(T * ptr) {
            if (!isSearchTree)
                return NULL;

            BinaryTreeNode<T*> *re = new BinaryTreeNode<T*>(ptr);
            insert(re);

            return re;
        }
        /*
         * find - 二叉搜索树查找元素
         *
         * @data: 目标元素
         */
        BinaryTreeNode<T*> * find(T const & data) {
            BinaryTreeNode<T*> * re = this->mRoot;

            while (NULL != re) {
                if (data < *(re->key))
                    re = re->l;
                else if (data > *(re->key))
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
        void remove(BinaryTreeNode<T*> *node) {
            if (NULL == node)
                return;

            if (NULL == node->l)
                this->replace_subtree(node, node->r);
            else if (NULL == node->r)
                this->replace_subtree(node, node->l);
            else {
                BinaryTreeNode<T*> *n = node->r->subtree_min_node();
                if (node != n->p) {
                    this->replace_subtree(n, n->r);
                    n->r = node->r;
                    n->r->p = n;
                }

                this->replace_subtree(node, n);
                n->l = node->l;
                n->l->p = n;
            }

            if (isSearchTree)
                delete node;
        }
        /*
         * remove - 二叉搜索树删除元素
         *
         * @node: 目标元素
         */
        void remove(T const & data) { remove(find(data)); }
};

#endif



