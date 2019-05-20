#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <binary_tree.h>

struct int_btree_node {
    int key;
    struct btree_node n;
};

int compare_fun(const struct btree_node *a, const struct btree_node *b)
{
    struct int_btree_node *p_a = ContainerOf(a, struct int_btree_node, n);
    struct int_btree_node *p_b = ContainerOf(b, struct int_btree_node, n);

    return p_a->key - p_b->key;
}



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

    printf("先序遍历:");
    struct btree_node *tmp = btree_preorder_traversal(&(nodes[0].n), &deque);
    while (0 != tmp) {
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
        tmp = btree_preorder_traversal(&(nodes[0].n), &deque);
    }
    printf("\n");

    printf("中序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_inorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_inorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("后序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_postorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_postorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    struct int_btree_node *nodes1 = (struct int_btree_node*)malloc(5 * sizeof(struct int_btree_node));
    for (int i = 0; i < 5; i++) {
        nodes1[i].key = i;
        init_btree_node(&(nodes1[i].n));
    }

    create_btree(&(nodes1[1].n), &(nodes1[3].n), &(nodes1[4].n));
    create_btree(&(nodes1[0].n), &(nodes1[1].n), &(nodes1[2].n));
    create_btree(&(nodes[2].n), &(nodes1[0].n), 0);

    printf("先序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_preorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_preorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("中序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_inorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_inorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("后序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_postorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_postorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");


    struct int_btree_node *nodes2 = (struct int_btree_node*)malloc(5 * sizeof(struct int_btree_node));
    for (int i = 0; i < 5; i++) {
        nodes2[i].key = i + 10;
        init_btree_node(&(nodes2[i].n));
    }

    create_btree(&(nodes2[1].n), &(nodes2[3].n), &(nodes2[4].n));
    create_btree(&(nodes2[0].n), &(nodes2[1].n), &(nodes2[2].n));

    btree_replace_subtree(NULL, &(nodes1[0].n), &(nodes2[0].n));

    printf("先序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_preorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_preorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("中序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_inorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_inorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("后序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_postorder_traversal(&(nodes[0].n), &deque); 0 != tmp; tmp = btree_postorder_traversal(&(nodes[0].n), &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("%s: ok\n", __FUNCTION__);
    printf(">>>\n");

    free(nodes);
    free(nodes1);
    free(nodes2);
}

int test_binary_search_tree()
{
    printf("%s: start\n", __FUNCTION__);

    struct int_btree_node *nodes = (struct int_btree_node*)malloc(5 * sizeof(struct int_btree_node));
    for (int i = 0; i < 5; i++) {
        nodes[i].key = i;
        init_btree_node(&(nodes[i].n));
    }

    btree_compare_fun fun = compare_fun;
    struct btree_node *root = &(nodes[2].n);

    btree_insert(root, &(nodes[4].n), fun);
    btree_insert(root, &(nodes[0].n), fun);
    btree_insert(root, &(nodes[1].n), fun);
    btree_insert(root, &(nodes[3].n), fun);

    deque_btree_node_ptr deque;
    deque_btree_node_ptr_init(&deque);

    printf("中序遍历:");
    struct btree_node *tmp = btree_inorder_traversal(root, &deque);
    while (0 != tmp) {
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
        tmp = btree_inorder_traversal(root, &deque);
    }
    printf("\n");

    printf("后序遍历:");
    tmp = btree_postorder_traversal(root, &deque);
    while (0 != tmp) {
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
        tmp = btree_postorder_traversal(root, &deque);
    }
    printf("\n");

    printf("最小值:%d, 遍历:", ContainerOf(btree_minimum(root), struct int_btree_node, n)->key);
    for (tmp = btree_minimum(root); tmp != NULL; tmp = btree_successor(tmp))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("最大值:%d, 遍历:", ContainerOf(btree_maximum(root), struct int_btree_node, n)->key);
    for (tmp = btree_maximum(root); tmp != NULL; tmp = btree_predecessor(tmp))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    struct int_btree_node snode;
    snode.key = 3;
    printf("find key: %d\n", ContainerOf(btree_find(root, &(snode.n), fun), struct int_btree_node, n)->key);

    printf("-------- remove %d ----------\n", ContainerOf(root, struct int_btree_node, n)->key);
    btree_remove(&root, root);
 
    printf("中序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_inorder_traversal(root, &deque); 0 != tmp; tmp = btree_inorder_traversal(root, &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("-------- remove %d ----------\n", ContainerOf(root, struct int_btree_node, n)->key);
    btree_remove(&root, root);

    printf("中序遍历:");
    deque_btree_node_ptr_clear(&deque);
    for (tmp = btree_inorder_traversal(root, &deque); 0 != tmp; tmp = btree_inorder_traversal(root, &deque))
        printf("%d ", ContainerOf(tmp, struct int_btree_node, n)->key);
    printf("\n");

    printf("%s: ok\n", __FUNCTION__);
    printf(">>>\n");
}

int main() {
    test_create();
    test_binary_search_tree();
}

