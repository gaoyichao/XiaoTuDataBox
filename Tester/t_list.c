
#include <list.h>
#include <stdlib.h>
#include <stdio.h>

struct double_node {
    double key;
    struct list_head list;
};

int main() {
    struct list_head stack;
    init_list_head(&stack);

    struct double_node *nodes = (struct double_node *)malloc(5 * sizeof(struct double_node));
    for (int i = 0; i < 5; i++) {
        nodes[i].key = 1.1 + 0.1 * i;
        init_list_head(&(nodes[i].list));
        list_add(&(nodes[i].list), &stack);
    }

    for (int i = 0; i < 5; i++) {
        struct double_node *pnode = list_entry(stack.next, struct double_node, list);
        printf("%f\n", pnode->key);
        list_del(stack.next);
    }

    for (int i = 0; i < 5; i++) {
        nodes[i].key = 1.1 + 0.1 * i;
        init_list_head(&(nodes[i].list));
        list_add_tail(&(nodes[i].list), &stack);
    }

    for (int i = 0; i < 5; i++) {
        struct double_node *pnode = list_entry(stack.prev, struct double_node, list);
        printf("%f\n", pnode->key);
        list_del(stack.prev);
    }

    free(nodes);
}

