#ifndef BINARYTREENODE_HPP
#define BINARYTREENODE_HPP

template <class T> class BinaryTree;

template <class T>
class BinaryTreeNode {
    friend class BinaryTree<T>;
    public:
        BinaryTreeNode() : parent(NULL), left(NULL), right(NULL) { }
        BinaryTreeNode(T const & data) : parent(NULL), left(NULL), right(NULL), key(data) { }

    private:
        /*
         * 屏蔽拷贝构造函数和赋值运算
         */
        BinaryTreeNode(BinaryTreeNode const &node) {}
        BinaryTreeNode & operator = (BinaryTreeNode const &node) {}

    public:
        BinaryTreeNode & parent_node() { return *parent; }
        BinaryTreeNode * parent_ptr() { return parent; }
        BinaryTreeNode & left_node() { return *left; }
        BinaryTreeNode * left_ptr() { return left; }
        BinaryTreeNode & right_node() { return *right; }
        BinaryTreeNode * right_ptr() { return right; }

        bool is_root() const { return NULL == parent; }
        bool is_leaf() const { return (NULL == left && NULL == right); }
        bool has_left() const { return NULL == left; }
        bool has_right() const { return NULL == right; }
    public:
        /*
         * update_left - 更新左子树
         *
         * return: 原左子树根节点,保持其父节点,由使用者负责
         */
        BinaryTreeNode * update_left(BinaryTreeNode *node) {
            BinaryTreeNode * re = left;

            left = node;
            if (NULL != node)
                node->parent = this;

            return re;
        }
        /*
         * update_right - 更新右子树
         *
         * return: 原右子树根节点,保持其父节点,由使用者负责
         */
        BinaryTreeNode * update_right(BinaryTreeNode *node) {
            BinaryTreeNode * re = right;

            right = node;
            if (NULL != node)
                node->parent = this;

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

            while (NULL != root->left)
                root = root->left;

            return root;
        }
        /*
         * subtree_max_node - 获取以当前节点为根的子树中的最大节点(最右节点)
         */
        BinaryTreeNode * subtree_max_node() {
            BinaryTreeNode *root = this;

            while (NULL != root->right)
                root = root->right;

            return root;
        }
        /*
         * predecessor - 获取当前节点的前驱
         */
        BinaryTreeNode * predecessor() {
            if (NULL != left)
                return left->subtree_max_node();

            BinaryTreeNode *re = parent;
            BinaryTreeNode *node = this;
            while ((NULL != re) && (node == re->left)) {
                node = re;
                re = re->parent;
            }
            return re;
        }
        /*
         * successor - 获取当前节点的后继
         */
        BinaryTreeNode * successor() {
            if (NULL != right)
                return right->subtree_min_node();

            BinaryTreeNode *re = parent;
            BinaryTreeNode *node = this;
            while ((NULL != re) && (node == re->right)) {
                node = re;
                re = re->parent;
            }
            return re;
        }

    public:
        BinaryTreeNode & operator = (T const &data) { key = data; }
        & operator T() { return key; }
        & operator const T() const { return key; }

    public:
        T key;
    protected:
        BinaryTreeNode *parent;
        BinaryTreeNode *left;
        BinaryTreeNode *right;
};

#endif

