#include <binary_tree.h>
#include <assert.h>

#ifdef  __cplusplus  
extern "C" {  
#endif 

#define T btree_node_ptr
#define TEMPLATE_TYPE(a) a ##_btree_node_ptr
#define TEMPLATE_FUNCTION(a,b) a ##_btree_node_ptr_## b
#include "deque.c.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T


/*
 * init_btree_node - 初始化二叉树结点
 *
 * @node: 目标节点
 */
void init_btree_node(struct btree_node* node) {
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
}

/*
 * create_btree - 构建二叉树
 *
 * @root: 二叉树根节点
 * @lroot: 左子树根节点
 * @rroot: 右子树根节点
 */
void create_btree(struct btree_node *root, struct btree_node *lroot, struct btree_node *rroot) {
    assert(NULL != root);
    if (NULL != lroot) {
        root->left = lroot;
        lroot->parent = root;
    }

    if (NULL != rroot) {
        root->right = rroot;
        rroot->parent = root;
    }
}
/*
 * btree_node_is_leaf - 判定目标节点是否是叶子节点 
 *
 * @node: 目标节点
 */
BOOL btree_node_is_leaf(struct btree_node *node) {
    if ((NULL == node->left) && (NULL == node->right))
        return True;
    return False;
}
/*
 * btree_replace_subtree - 用v替换节点u 
 *
 * 该函数返回之后,v替代了u在二叉树中位置;
 * 仍然保持u的parent指针不变,用于记录u原来的位置
 *
 * @root: 根节点指针的指针,如果u是根节点,则会修改该值标识着根节点发生了改变
 * @u: 被替换的节点,是root的后代
 * @v: 将要替换的子树根节点
 */
void btree_replace_subtree(struct btree_node **root, struct btree_node *u, struct btree_node *v)
{
    if (NULL == u)
        return;

    if (NULL == u->parent && NULL != root)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (NULL != v)
        v->parent = u->parent;
}

/*
 * btree_preorder_traversal - 先序遍历二叉树,每次只返回一个元素
 *
 * @root: 目标二叉树根节点
 * @pdeque: 遍历中间缓存
 */
struct btree_node * btree_preorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque) {
    struct btree_node *re;

    int size = deque_btree_node_ptr_size(pdeque);
    if (0 == size) {
        re = root;
    } else {
        deque_btree_node_ptr_pop_back(pdeque, &re);
        if (NULL == re)
            return NULL;
    }

    if (NULL != re->right)
        deque_btree_node_ptr_push_back(pdeque, re->right);
    if (NULL != re->left)
        deque_btree_node_ptr_push_back(pdeque, re->left);

    if (0 == deque_btree_node_ptr_size(pdeque))
        deque_btree_node_ptr_push_back(pdeque, NULL);

    return re;
}
/*
 * btree_ineorder_traversal - 中序遍历二叉树,每次只返回一个元素
 *
 * @root: 目标二叉树根节点
 * @pdeque: 遍历中间缓存
 */
struct btree_node * btree_inorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque) {
    struct btree_node *re;

    int size = deque_btree_node_ptr_size(pdeque);
    if (0 == size) {
        re = root;
        while (NULL != re->left) {
            deque_btree_node_ptr_push_back(pdeque, re);
            re = re->left;
        }
    } else {
        deque_btree_node_ptr_pop_back(pdeque, &re);
        if (NULL == re)
            return NULL;
    }

    if (NULL != re->right) {
        deque_btree_node_ptr_push_back(pdeque, re->right);
        root = re->right;
        while (NULL != root->left) {
            deque_btree_node_ptr_push_back(pdeque, root->left);
            root = root->left;
        }
    }

    if (0 == deque_btree_node_ptr_size(pdeque))
        deque_btree_node_ptr_push_back(pdeque, NULL);
    return re;
}
/*
 * btree_postorder_traversal - 后序遍历二叉树,每次只返回一个元素
 *
 * @root: 目标二叉树根节点
 * @pdeque: 遍历中间缓存
 */
struct btree_node * btree_postorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque) {
    struct btree_node *re, *tmp;

    int size = deque_btree_node_ptr_size(pdeque);
    if (0 == size) {
        deque_btree_node_ptr_push_back(pdeque, root);
        deque_btree_node_ptr_push_back(pdeque, root);
    }

    deque_btree_node_ptr_pop_back(pdeque, &re);
    if (NULL == re)
        return NULL;
    if (0 == deque_btree_node_ptr_size(pdeque))
        deque_btree_node_ptr_push_back(pdeque, NULL);
    deque_btree_node_ptr_peek_back(pdeque, &tmp);

    while (tmp == re) {
        if (NULL != re->right) {
            deque_btree_node_ptr_push_back(pdeque, re->right);
            deque_btree_node_ptr_push_back(pdeque, re->right);
        }

        if (NULL != re->left) {
            deque_btree_node_ptr_push_back(pdeque, re->left);
            deque_btree_node_ptr_push_back(pdeque, re->left);
        }

        deque_btree_node_ptr_pop_back(pdeque, &re);
        deque_btree_node_ptr_peek_back(pdeque, &tmp);
    }

    return re;
}

/*
 * btree_minimum - 二叉搜索树最小节点
 *
 * @root: 目标二叉树根节点
 */
struct btree_node * btree_minimum(struct btree_node *root) {
    if (NULL == root)
        return NULL;

    while (NULL != root->left)
        root = root->left;

    return root;
}
/*
 * btree_maximum - 二叉搜索树最大节点
 *
 * @root: 目标二叉树根节点
 */
struct btree_node * btree_maximum(struct btree_node *root) {
    if (NULL == root)
        return NULL;

    while (NULL != root->right)
        root = root->right;

    return root;
}

/*
 * btree_predecessor - 考察节点的前驱
 *
 * @node: 考察节点
 */
struct btree_node * btree_predecessor(struct btree_node *node) {
    if (NULL != node->left)
        return btree_maximum(node->left);

    struct btree_node *y = node->parent;
    while ((NULL != y) && (node == y->left)) {
        node = y;
        y = y->parent;
    }

    return y;
}
/*
 * btree_predecessor - 考察节点的后继
 *
 * @node: 考察节点
 */
struct btree_node * btree_successor(struct btree_node *node) {
    if (NULL != node->right)
        return btree_minimum(node->right);

    struct btree_node *y = node->parent;
    while ((NULL != y) && (node == y->right)) {
        node = y;
        y = y->parent;
    }

    return y;
}
/*
 * btree_insert - 二叉搜索树插入元素
 *
 * @root: 目标二叉树根节点
 * @node: 待插入节点
 * @compare: 节点比较函数入口,比较函数由用户实现
 */
struct btree_node * btree_insert(struct btree_node *root, struct btree_node *node, btree_compare_fun compare) {
    if (NULL == root)
        return NULL;


    struct btree_node *y = NULL;
    struct btree_node *x = root;

    while (NULL != x) {
        y = x;
        if (compare(node, x) < 0)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (compare(node, y) < 0)
        y->left = node;
    else
        y->right = node;

    return node;
}
/*
 * btree_find - 二叉搜索树查找元素
 *
 * @root: 目标二叉树根节点
 * @node: 待插入节点
 * @compare: 节点比较函数入口,比较函数由用户实现
 */
struct btree_node * btree_find(struct btree_node *root, struct btree_node *node, btree_compare_fun compare) {
    while (NULL != root) {
        int com = compare(node, root);

        if (com < 0)
            root = root->left;
        else if (com > 0)
            root = root->right;
        else
            break;
    }
    return root;
}
/*
 * btree_remove - 移除二叉树中的一个指定节点
 *
 * @root: 二叉树的根节点指针的指针,node可能是一个根节点
 * @node: 待移除的节点
 */
struct btree_node * btree_remove(struct btree_node **root, struct btree_node *node) {
    if (NULL == node->left)
        btree_replace_subtree(root, node, node->right);
    else if (NULL == node->right)
        btree_replace_subtree(root, node, node->left);
    else {
        struct btree_node *n = btree_minimum(node->right);
        if (node != n->parent) {
            btree_replace_subtree(root, n, n->right);
            n->right = node->right;
            n->right->parent = n;
        }

        btree_replace_subtree(root, node, n);
        n->left = node->left;
        n->left->parent = n;
    }
}

#ifdef  __cplusplus  
}  
#endif 



