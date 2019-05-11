#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <binary_tree.h>

struct int_btree_node {
    int key;
    struct btree_node n;
};

int test_create()
{
    printf("%s: start\n", __FUNCTION__);

    struct int_btree_node *nodes = (struct int_btree_node*)malloc(5 * sizeof(struct int_btree_node));
    for (int i = 0; i < 5; i++) {
        nodes[i].key = i;
        init_btree_node(&(nodes[i].n));
    }

    create_btree(&(nodes[1].n), &(nodes[3].n), &(nodes[4].n));
    create_btree(&(nodes[0].n), &(nodes[1].n), &(nodes[2].n));

    deque_btree_node_ptr deque;
    deque_btree_node_ptr_init(&deque);

    printf("先序遍历:\n");
    struct btree_node *tmp = btree_preorder_traversal(&(nodes[0].n), &deque);
    while (0 != tmp) {
        printf("%d\n", ContainerOf(tmp, struct int_btree_node, n)->key);
        tmp = btree_preorder_traversal(&(nodes[0].n), &deque);
    }

    printf("中序遍历:\n");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_inorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_inorder_traversal(&(nodes[0].n), &deque))
        printf("%d\r\n", ContainerOf(tmp, struct int_btree_node, n)->key);


    printf("后序遍历:\n");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_postorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_postorder_traversal(&(nodes[0].n), &deque))
        printf("%d\r\n", ContainerOf(tmp, struct int_btree_node, n)->key);

    struct int_btree_node *nodes1 = (struct int_btree_node*)malloc(5 * sizeof(struct int_btree_node));
    for (int i = 0; i < 5; i++) {
        nodes1[i].key = i;
        init_btree_node(&(nodes1[i].n));
    }

    create_btree(&(nodes1[1].n), &(nodes1[3].n), &(nodes1[4].n));
    create_btree(&(nodes1[0].n), &(nodes1[1].n), &(nodes1[2].n));
    create_btree(&(nodes[2].n), &(nodes1[0].n), 0);

    printf("先序遍历:\n");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_preorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_preorder_traversal(&(nodes[0].n), &deque))
        printf("%d\n", ContainerOf(tmp, struct int_btree_node, n)->key);

    printf("中序遍历:\n");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_inorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_inorder_traversal(&(nodes[0].n), &deque))
        printf("%d\r\n", ContainerOf(tmp, struct int_btree_node, n)->key);


    printf("后序遍历:\n");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_postorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_postorder_traversal(&(nodes[0].n), &deque))
        printf("%d\r\n", ContainerOf(tmp, struct int_btree_node, n)->key);


    printf("%s: ok\n", __FUNCTION__);
}


int main() {
    test_create();
}

