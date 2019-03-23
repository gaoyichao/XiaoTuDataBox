#include <gtest/gtest.h>

#include <list.h>

struct double_list {
    double key;
    struct list_head list;
};

TEST(list, init)
{
    struct list_head head;
    init_list_head(&head);

    EXPECT_EQ(&head, head.next);
    EXPECT_EQ(&head, head.prev);
}



