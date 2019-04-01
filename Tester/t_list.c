#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <list.h>

struct double_node {
    double key;
    struct list_head list;
};

int test_stack()
{
    printf("%s: start\n", __FUNCTION__);

    struct list_head stack;
    init_list_head(&stack);

    struct double_node *nodes = (struct double_node *)malloc(5 * sizeof(struct double_node));
    for (int i = 0; i < 5; i++) {
        nodes[i].key = 1.1 + 0.1 * i;
        init_list_head(&(nodes[i].list));
        list_add(&(nodes[i].list), &stack);
    }

    for (int i = 5; i > 0; i--) {
        struct double_node *pnode = list_entry(stack.next, struct double_node, list);
        assert((pnode->key) == (1.1 + 0.1 * (i-1)));
        list_del(stack.next);
    }

    for (int i = 0; i < 5; i++) {
        nodes[i].key = 1.1 + 0.1 * i;
        init_list_head(&(nodes[i].list));
        list_add_tail(&(nodes[i].list), &stack);
    }

    for (int i = 5; i > 0; i--) {
        struct double_node *pnode = list_entry(stack.prev, struct double_node, list);
        assert((pnode->key) == (1.1 + 0.1 * (i-1)));
        list_del(stack.prev);
    }

    free(nodes);
    printf("%s: ok\n", __FUNCTION__);
}

int test_queue()
{
    printf("%s: start\n", __FUNCTION__);

    struct list_head queue;
    init_list_head(&queue);

    struct double_node *nodes = (struct double_node *)malloc(5 * sizeof(struct double_node));
    for (int i = 0; i < 5; i++) {
        nodes[i].key = 1.1 + 0.1 * i;
        init_list_head(&(nodes[i].list));
        list_add_tail(&(nodes[i].list), &queue);
    }

    for (int i = 0; i < 5; i++) {
        struct double_node *pnode = list_entry(queue.next, struct double_node, list);
        assert((pnode->key) == (1.1 + 0.1 * i));
        list_del(queue.next);
    }


    for (int i = 0; i < 5; i++) {
        nodes[i].key = 1.1 + 0.1 * i;
        init_list_head(&(nodes[i].list));
        list_add(&(nodes[i].list), &queue);
    }

    for (int i = 0; i < 5; i++) {
        struct double_node *pnode = list_entry(queue.prev, struct double_node, list);
        assert((pnode->key) == (1.1 + 0.1 * i));
        list_del(queue.prev);
    }

    free(nodes);
    printf("%s: ok\n", __FUNCTION__);
}

int main() {
    test_stack();
    test_queue();
}

