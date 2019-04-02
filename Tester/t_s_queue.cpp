#include <gtest/gtest.h>
#include <stdio.h>

#define T double 
#define TEMPLATE_TYPE(a) a ##_double
#define TEMPLATE_FUNCTION(a,b) a ##_double_## b
#include "s_queue.h.h"
#include "s_queue.c.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T

TEST(s_queue, init)
{
    double queue_buf[64];
    s_queue_double queue;

    EXPECT_EQ(s_queue_double_init(&queue, queue_buf, 64), 0);
    EXPECT_EQ(s_queue_double_size(&queue), 0);
    EXPECT_TRUE(s_queue_double_empty(&queue));
    EXPECT_FALSE(s_queue_double_full(&queue));
    EXPECT_EQ(s_queue_double_capacity(&queue), 64);
    EXPECT_EQ(s_queue_double_available(&queue), 64);

    for (int i = 0; i < 64; i++) {
        EXPECT_EQ(s_queue_double_enqueue(&queue, 1.2 * i), QUEUE_NOERR);
        EXPECT_EQ(s_queue_double_size(&queue), i+1);
    }
    EXPECT_EQ(s_queue_double_enqueue(&queue, 3.14), QUEUE_FULL);

    double tmp;
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(s_queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(s_queue_double_enqueue(&queue, 1.2 * i), QUEUE_NOERR);
    }

    for (int i = 10; i < 64; i++) {
        EXPECT_EQ(s_queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(s_queue_double_dequeue(&queue, &tmp), QUEUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(s_queue_double_dequeue(&queue, &tmp), QUEUE_EMPTY);
    
    s_queue_double_clear(&queue);
    EXPECT_EQ(s_queue_double_size(&queue), 0);
}




