#include <gtest/gtest.h>
#include <stdio.h>


#define T double 
#define TEMPLATE_TYPE(a) a ##_double
#define TEMPLATE_FUNCTION(a,b) a ##_double_## b
#include "deque.h.h"
#include "deque.c.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T

TEST(deque, init)
{
    deque_double deque;

    EXPECT_EQ(deque_double_init(&deque), 0);
    EXPECT_EQ(deque_double_size(&deque), 0);
    EXPECT_TRUE(deque_double_empty(&deque));
    EXPECT_FALSE(deque_double_full(&deque));
    EXPECT_EQ(deque_double_capacity(&deque), 4);
    EXPECT_EQ(deque_double_available(&deque), 4);
}


TEST(deque, push_back_pop_front)
{
    deque_double deque;
    EXPECT_EQ(deque_double_init(&deque), 0);

    double tmp;
    for (int i = 0; i < 13; i++) {
        EXPECT_EQ(deque_double_push_back(&deque, 1.2 * i), DEQUE_NOERR);
        EXPECT_EQ(deque_double_size(&deque), i+1);
    }
    EXPECT_EQ(deque_double_size(&deque), 13);
    EXPECT_EQ(deque_double_capacity(&deque), 16);
    deque_double_peek_front(&deque, &tmp);
    EXPECT_EQ(tmp, 0);
    deque_double_peek_back(&deque, &tmp);
    EXPECT_EQ(tmp, 1.2 * 12);

    for (int i = 0; i < 11; i++) {
        EXPECT_EQ(deque_double_pop_front(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 2);
    EXPECT_EQ(deque_double_capacity(&deque), 16);

    for (int i = 13; i < 20; i++) {
        EXPECT_EQ(deque_double_push_back(&deque, 1.2 * i), DEQUE_NOERR);
    }
    EXPECT_EQ(deque_double_size(&deque), 9);
    EXPECT_EQ(deque_double_capacity(&deque), 16);

    for (int i = 11; i < 17; i++) {
        EXPECT_EQ(deque_double_pop_front(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 3);
    EXPECT_EQ(deque_double_capacity(&deque), 16);

    deque_double_rearrange(&deque);
    for (int i = 17; i < 19; i++) {
        EXPECT_EQ(deque_double_pop_front(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 1);

    for (int i = 20; i < 36; i++) {
        EXPECT_EQ(deque_double_push_back(&deque, 1.2 * i), DEQUE_NOERR);
    }
    EXPECT_EQ(deque_double_size(&deque), 17);
    EXPECT_EQ(deque_double_capacity(&deque), 32);

    deque_double_rearrange(&deque);
    for (int i = 19; i < 35; i++) {
        EXPECT_EQ(deque_double_pop_front(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 1);

    EXPECT_EQ(deque_double_pop_front(&deque, &tmp), DEQUE_NOERR);
    EXPECT_EQ(tmp, 1.2 * 35);
    EXPECT_TRUE(deque_double_empty(&deque));

    deque_double_destroy(&deque);
}

TEST(deque, push_front_pop_back)
{
    deque_double deque;
    EXPECT_EQ(deque_double_init(&deque), 0);

    for (int i = 0; i < 13; i++) {
        EXPECT_EQ(deque_double_push_front(&deque, 1.2 * i), DEQUE_NOERR);
        EXPECT_EQ(deque_double_size(&deque), i+1);
    }
    EXPECT_EQ(deque_double_size(&deque), 13);
    EXPECT_EQ(deque_double_capacity(&deque), 16);

    double tmp;
    for (int i = 0; i < 11; i++) {
        EXPECT_EQ(deque_double_pop_back(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 2);
    EXPECT_EQ(deque_double_capacity(&deque), 16);

    for (int i = 13; i < 20; i++) {
        EXPECT_EQ(deque_double_push_front(&deque, 1.2 * i), DEQUE_NOERR);
    }
    EXPECT_EQ(deque_double_size(&deque), 9);
    EXPECT_EQ(deque_double_capacity(&deque), 16);

    for (int i = 11; i < 17; i++) {
        EXPECT_EQ(deque_double_pop_back(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 3);
    EXPECT_EQ(deque_double_capacity(&deque), 16);

    deque_double_rearrange(&deque);
    for (int i = 17; i < 19; i++) {
        EXPECT_EQ(deque_double_pop_back(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 1);

    for (int i = 20; i < 36; i++) {
        EXPECT_EQ(deque_double_push_front(&deque, 1.2 * i), DEQUE_NOERR);
    }
    EXPECT_EQ(deque_double_size(&deque), 17);
    EXPECT_EQ(deque_double_capacity(&deque), 32);

    deque_double_rearrange(&deque);
    for (int i = 19; i < 35; i++) {
        EXPECT_EQ(deque_double_pop_back(&deque, &tmp), DEQUE_NOERR);
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(deque_double_size(&deque), 1);

    EXPECT_EQ(deque_double_pop_back(&deque, &tmp), DEQUE_NOERR);
    EXPECT_EQ(tmp, 1.2 * 35);
    EXPECT_TRUE(deque_double_empty(&deque));

    deque_double_destroy(&deque);
}

TEST(deque, push_back_pop_back)
{
    deque_double deque;

    EXPECT_EQ(deque_double_init(&deque), 0);
    EXPECT_EQ(deque_double_size(&deque), 0);
    EXPECT_TRUE(deque_double_empty(&deque));
    EXPECT_FALSE(deque_double_full(&deque));
    EXPECT_EQ(deque_double_capacity(&deque), 4);
    EXPECT_EQ(deque_double_available(&deque), 4);

    for (int i = 0; i < 5; i++) {
        deque_double_push_back(&deque, 1.1 + i);
        EXPECT_EQ(deque_double_size(&deque), 1 + i);
    }
    EXPECT_EQ(deque_double_size(&deque), 5);

    double tmp;
    for (int i = 5; i > 0; i--) {
        deque_double_pop_back(&deque, &tmp);
        EXPECT_EQ(deque_double_size(&deque), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(deque_double_size(&deque), 0);

    deque_double_destroy(&deque);
}


TEST(deque, push_front_pop_front)
{
    deque_double deque;

    EXPECT_EQ(deque_double_init(&deque), 0);
    EXPECT_EQ(deque_double_size(&deque), 0);
    EXPECT_TRUE(deque_double_empty(&deque));
    EXPECT_FALSE(deque_double_full(&deque));
    EXPECT_EQ(deque_double_capacity(&deque), 4);
    EXPECT_EQ(deque_double_available(&deque), 4);

    for (int i = 0; i < 5; i++) {
        deque_double_push_front(&deque, 1.1 + i);
        EXPECT_EQ(deque_double_size(&deque), 1 + i);
    }
    EXPECT_EQ(deque_double_size(&deque), 5);

    double tmp;
    for (int i = 5; i > 0; i--) {
        deque_double_pop_front(&deque, &tmp);
        EXPECT_EQ(deque_double_size(&deque), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(deque_double_size(&deque), 0);

    deque_double_destroy(&deque);
}


