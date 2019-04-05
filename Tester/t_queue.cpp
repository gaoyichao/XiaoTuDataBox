#include <gtest/gtest.h>
#include <stdio.h>


#define T double 
#define TEMPLATE_TYPE(a) a ##_double
#define TEMPLATE_FUNCTION(a,b) a ##_double_## b
#include "queue.h.h"
#include "queue.c.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T


TEST(queue, init)
{
    queue_double queue;

    EXPECT_EQ(queue_double_init(&queue), 0);
    EXPECT_EQ(queue_double_size(&queue), 0);
    EXPECT_TRUE(queue_double_empty(&queue));
    EXPECT_FALSE(queue_double_full(&queue));
    EXPECT_EQ(queue_double_capacity(&queue), 4);
    EXPECT_EQ(queue_double_available(&queue), 4);

    for (int i = 0; i < 13; i++) {
        EXPECT_EQ(queue_double_enqueue(&queue, 1.2 * i), QUEUE_NOERR);
        EXPECT_EQ(queue_double_size(&queue), i+1);
    }
    EXPECT_EQ(queue_double_size(&queue), 13);
    EXPECT_EQ(queue_double_capacity(&queue), 16);

    double tmp;
    for (int i = 0; i < 11; i++) {
        EXPECT_EQ(queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(queue_double_size(&queue), 2);
    EXPECT_EQ(queue_double_capacity(&queue), 16);

    for (int i = 13; i < 20; i++) {
        EXPECT_EQ(queue_double_enqueue(&queue, 1.2 * i), QUEUE_NOERR);
    }
    EXPECT_EQ(queue_double_size(&queue), 9);
    EXPECT_EQ(queue_double_capacity(&queue), 16);

    for (int i = 11; i < 17; i++) {
        EXPECT_EQ(queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(queue_double_size(&queue), 3);
    EXPECT_EQ(queue_double_capacity(&queue), 16);

    queue_double_rearrange(&queue);
    for (int i = 17; i < 19; i++) {
        EXPECT_EQ(queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(queue_double_size(&queue), 1);

    for (int i = 20; i < 36; i++) {
        EXPECT_EQ(queue_double_enqueue(&queue, 1.2 * i), QUEUE_NOERR);
    }
    EXPECT_EQ(queue_double_size(&queue), 17);
    EXPECT_EQ(queue_double_capacity(&queue), 32);

    queue_double_rearrange(&queue);
    for (int i = 19; i < 35; i++) {
        EXPECT_EQ(queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(queue_double_size(&queue), 1);

    EXPECT_EQ(queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
    EXPECT_EQ(tmp, 1.2 * 35);
    EXPECT_TRUE(queue_double_empty(&queue));

    queue_double_destroy(&queue);
}



