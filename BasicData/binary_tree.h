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

#define T btree_node_ptr
#define TEMPLATE_TYPE(a) a ##_btree_node_ptr
#define TEMPLATE_FUNCTION(a,b) a ##_btree_node_ptr_## b
#include "deque.h.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T

void init_btree_node(struct btree_node* node);
void create_btree(struct btree_node *root, struct btree_node *lroot, struct btree_node *rroot);

struct btree_node * btree_preorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque); 
struct btree_node * btree_inorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque); 
struct btree_node * btree_postorder_traversal(struct btree_node *root, deque_btree_node_ptr *pdeque); 


#ifdef  __cplusplus  
}  
#endif 

#endif

