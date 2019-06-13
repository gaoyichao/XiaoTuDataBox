#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <types.h>

#ifdef  __cplusplus  
extern "C" {  
#endif 

struct btree_node {
    struct btree_node *parent;
    struct btree_node *left;
    struct btree_node *right;
};

typedef struct btree_node * btree_node_ptr;
typedef int (*btree_compare_fun)(const struct btree_node *a, const struct btree_node *b);

#define T btree_node_ptr
#define TEMPLATE_TYPE(a) a ##_btree_node_ptr
#define TEMPLATE_FUNCTION(a,b) a ##_btree_node_ptr_## b
#include "deque.h.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T

void init_btree_node(struct btree_node* node);
void create_btree(struct btree_node *root, struct btree_node *lroot, struct btree_node *rroot);
BOOL btree_node_is_leaf(struct btree_node *node);

void btree_replace_subtree(struct btree_node **root, struct btree_node *u, struct btree_node *v);

struct btree_node * btree_preorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque); 
struct btree_node * btree_inorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque); 
struct btree_node * btree_postorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque); 

struct btree_node * btree_minimum(struct btree_node *root);
struct btree_node * btree_maximum(struct btree_node *root);

struct btree_node * btree_predecessor(struct btree_node *node);
struct btree_node * btree_successor(struct btree_node *node);

struct btree_node * btree_insert(struct btree_node *root, struct btree_node *node, btree_compare_fun compare); 
struct btree_node * btree_find(struct btree_node *root, struct btree_node *node, btree_compare_fun compare); 
void btree_remove(struct btree_node **root, struct btree_node *node);


#ifdef  __cplusplus  
}  
#endif 

#endif

