#ifndef BINARYTREENODE_HPP
#define BINARYTREENODE_HPP

template <class T> class BinaryTree;

template <class T>
class BinaryTreeNode {
    friend class BinaryTree<T>;
    public:
        BinaryTreeNode() : p(NULL), l(NULL), r(NULL) { }
        BinaryTreeNode(T const & data) : p(NULL), l(NULL), r(NULL), key(data) { }

    private:
        /*
         * 屏蔽拷贝构造函数和赋值运算
         */
        BinaryTreeNode(BinaryTreeNode const &node) {}
        BinaryTreeNode & operator = (BinaryTreeNode const &node) {}

    public:
        bool is_root() const { return NULL == p; }
        bool is_leaf() const { return (NULL == l && NULL == r); }
        bool has_left() const { return NULL == l; }
        bool has_right() const { return NULL == r; }
    public:
        /*
         * update_left - 更新左子树
         *
         * return: 原左子树根节点,保持其父节点,由使用者负责
         */
        BinaryTreeNode * update_left(BinaryTreeNode *node) {
            BinaryTreeNode * re = l;

            l = node;
            if (NULL != node)
                node->p = this;

            return re;
        }
        /*
         * update_right - 更新右子树
         *
         * return: 原右子树根节点,保持其父节点,由使用者负责
         */
        BinaryTreeNode * update_right(BinaryTreeNode *node) {
            BinaryTreeNode * re = r;

            r = node;
            if (NULL != node)
                node->p = this;

            return re;
        }

    public:
        /*****************************************************************
                    二叉搜索树相关成员
         *****************************************************************/
        /*
         * subtree_min_node - 获取以当前节点为根的子树中的最小节点(最左节点)
         */
        BinaryTreeNode * subtree_min_node() {
            BinaryTreeNode *root = this;

            while (NULL != root->l)
                root = root->l;

            return root;
        }
        /*
         * subtree_max_node - 获取以当前节点为根的子树中的最大节点(最右节点)
         */
        BinaryTreeNode * subtree_max_node() {
            BinaryTreeNode *root = this;

            while (NULL != root->r)
                root = root->r;

            return root;
        }
        /*
         * predecessor - 获取当前节点的前驱
         */
        BinaryTreeNode * predecessor() {
            if (NULL != l)
                return l->subtree_max_node();

            BinaryTreeNode *re = p;
            BinaryTreeNode *node = this;
            while ((NULL != re) && (node == re->l)) {
                node = re;
                re = re->p;
            }
            return re;
        }
        /*
         * successor - 获取当前节点的后继
         */
        BinaryTreeNode * successor() {
            if (NULL != r)
                return r->subtree_min_node();

            BinaryTreeNode *re = p;
            BinaryTreeNode *node = this;
            while ((NULL != re) && (node == re->r)) {
                node = re;
                re = re->p;
            }
            return re;
        }

    public:
        BinaryTreeNode & operator = (T const &data) { key = data; }
        & operator T() { return key; }
        & operator const T() const { return key; }

        BinaryTreeNode * parent() {
            if (NULL == this)
                return NULL;
            return this->p;
        }

        BinaryTreeNode * left() {
            if (NULL == this)
                return NULL;
            return l;
        }

        BinaryTreeNode * right() {
            if (NULL == this)
                return NULL;
            return r;
        }

        BinaryTreeNode * gparent() {
            BinaryTreeNode *_p = parent();
            return _p->parent();
        }

    public:
        T key;
        BinaryTreeNode *p;
        BinaryTreeNode *l;
        BinaryTreeNode *r;
};

#endif

