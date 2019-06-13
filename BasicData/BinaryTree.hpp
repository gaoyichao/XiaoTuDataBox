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

            if (NULL == u->parent && NULL != mRoot)
                mRoot = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;

            if (NULL != v)
                v->parent = u->parent;

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

            if (NULL != re->right)
                mPreOrderQueue.push_back(re->right);
            if (NULL != re->left)
                mPreOrderQueue.push_back(re->left);

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
                while (NULL != re->left) {
                    mInOrderQueue.push_back(re);
                    re = re->left;
                }
            } else {
                mInOrderQueue.pop_back(re);
                if (NULL == re)
                    return NULL;
            }

            if (NULL != re->right) {
                mInOrderQueue.push_back(re->right);
                BinaryTreeNode<T> *root = re->right;
                while (NULL != root->left) {
                    mInOrderQueue.push_back(root->left);
                    root = root->left;
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
                if (NULL != re->right) {
                    mPostOrderQueue.push_back(re->right);
                    mPostOrderQueue.push_back(re->right);
                }

                if (NULL != re->left) {
                    mPostOrderQueue.push_back(re->left);
                    mPostOrderQueue.push_back(re->left);
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
        /*
         * insert - 二叉搜索树插入元素
         *
         * @data: 插入元素
         */
        BinaryTreeNode<T> * insert(T const & data) {
            if (!mIsSearchTree)
                return NULL;

            BinaryTreeNode<T> *re = new BinaryTreeNode<T>(data);
            if (NULL == mRoot) {
                mRoot = re;
                return re;
            }

            BinaryTreeNode<T> *y = NULL;
            BinaryTreeNode<T> *x = mRoot;

            while (NULL != x) {
                y = x;
                if (re->key < x->key)
                    x = x->left;
                else
                    x = x->right;
            }

            re->parent = y;
            if (re->key < y->key)
                y->left = re;
            else
                y->right = re;

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
                    re = re->left;
                else if (data > re->key)
                    re = re->right;
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

            if (NULL == node->left)
                replace_subtree(node, node->right);
            else if (NULL == node->right)
                replace_subtree(node, node->left);
            else {
                BinaryTreeNode<T> *n = node->right->subtree_min_node();
                if (node != n->parent) {
                    replace_subtree(n, n->right);
                    n->right = node->right;
                    n->right->parent = n;
                }

                replace_subtree(node, n);
                n->left = node->left;
                n->left->parent = n;
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
