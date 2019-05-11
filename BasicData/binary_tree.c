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
    node->parent = node;
    node->left = node;
    node->right = node;
}

/*
 * create_btree - 构建二叉树
 *
 * @root: 二叉树根节点
 * @lroot: 左子树根节点
 * @rroot: 右子树根节点
 */
void create_btree(struct btree_node *root, struct btree_node *lroot, struct btree_node *rroot) {
    assert(0 != root);
    if (0 != lroot) {
        root->left = lroot;
        lroot->parent = root;
    } else {
        root->left = root;
    }

    if (0 != rroot) {
        root->right = rroot;
        rroot->parent = root;
    } else {
        root->right = root;
    }
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
        if (0 == re)
            return 0;
        if (0 == deque_btree_node_ptr_size(pdeque))
            deque_btree_node_ptr_push_back(pdeque, 0);
    }

    if (re != re->right)
        deque_btree_node_ptr_push_back(pdeque, re->right);
    if (re != re->left)
        deque_btree_node_ptr_push_back(pdeque, re->left);

    return re;
}
/*
 * btree_ineorder_traversal - 中序遍历二叉树,每次只返回一个元素
 *
 * @root: 目标二叉树根节点
 * @pdeque: 遍历中间缓存
 */
struct btree_node * btree_inorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque) {
    struct btree_node *re, *tmp;

    int size = deque_btree_node_ptr_size(pdeque);
    if (0 == size) {
        re = root;
        while (re != re->left) {
            deque_btree_node_ptr_push_back(pdeque, re);
            re = re->left;
        }
    } else {
        deque_btree_node_ptr_pop_back(pdeque, &re);
        if (0 == re)
            return 0;

        if (re != re->right) {
            deque_btree_node_ptr_push_back(pdeque, re->right);
            tmp = re->right;
            while (tmp != tmp->left) {
                deque_btree_node_ptr_push_back(pdeque, tmp->left);
                tmp = tmp->left;
            }
        }
    }

    if (0 == deque_btree_node_ptr_size(pdeque))
        deque_btree_node_ptr_push_back(pdeque, 0);
    return re;
}

struct btree_node * btree_postorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque) {
    struct btree_node *re, *tmp;

    int size = deque_btree_node_ptr_size(pdeque);
    if (0 == size) {
        deque_btree_node_ptr_push_back(pdeque, root);
        deque_btree_node_ptr_push_back(pdeque, root);
    }

    deque_btree_node_ptr_pop_back(pdeque, &re);
    if (0 == re)
        return 0;
    if (0 == deque_btree_node_ptr_size(pdeque))
        deque_btree_node_ptr_push_back(pdeque, 0);
    deque_btree_node_ptr_peek_back(pdeque, &tmp);

    while (tmp == re) {
        if (re != re->right) {
            deque_btree_node_ptr_push_back(pdeque, re->right);
            deque_btree_node_ptr_push_back(pdeque, re->right);
        }

        if (re != re->left) {
            deque_btree_node_ptr_push_back(pdeque, re->left);
            deque_btree_node_ptr_push_back(pdeque, re->left);
        }

        deque_btree_node_ptr_pop_back(pdeque, &re);
        deque_btree_node_ptr_peek_back(pdeque, &tmp);
    }

    return re;
}

#ifdef  __cplusplus  
}  
#endif 


