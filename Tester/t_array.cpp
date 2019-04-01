#include <gtest/gtest.h>

#define T double 
#define TEMPLATE_TYPE(a) a ##_double
#define TEMPLATE_FUNCTION(a,b) a ##_double_## b
#include "array.h.h"
#include "array.c.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T

TEST(array, init)
{
    array_double array0;

    EXPECT_EQ(array_double_init(&array0, 0), 0);
    EXPECT_EQ(array_double_size(&array0), 0);
    EXPECT_TRUE(array_double_empty(&array0));
    EXPECT_FALSE(array_double_full(&array0));
    EXPECT_GT(array_double_capacity(&array0), 0);
    EXPECT_EQ(array_double_available(&array0), 1);

    array_double_destroy(&array0);
}

TEST(array, init_copy)
{
    array_double array0;
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;

    EXPECT_EQ(array_double_init_copy(&array0, 4, datas), 0);
    EXPECT_EQ(array_double_size(&array0), 4);
    EXPECT_GT(array_double_capacity(&array0), 0);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(ARRAY(array0)[i], datas[i]);
    }

    for (int i = 0; i < 4; i++) {
        ARRAY(array0)[i] = 1.2 + datas[i];
        EXPECT_NE(ARRAY(array0)[i], datas[i]);
    }

    array_double_destroy(&array0);
}

TEST(array, element)
{
    array_double array0;

    EXPECT_EQ(array_double_init(&array0, 4), 0);
    EXPECT_EQ(array_double_size(&array0), 4);
    EXPECT_GT(array_double_capacity(&array0), 0);

    double *ptr = array_double_e_ptr(&array0, 2);
    *ptr = 3.14;
    EXPECT_EQ(ARRAY(array0)[2], 3.14);

    array_double_set(&array0, 0, 1.414);
    EXPECT_EQ(array_double_e(&array0, 0), 1.414);

    double tmp = 101.01;
    array_double_ptr_set(&array0, 0, &tmp);
    EXPECT_EQ(array_double_e(&array0, 0), tmp);

    const double *ptr1 = array_double_e_cptr(&array0, 1);
    EXPECT_EQ(*ptr1, ARRAY(array0)[1]);

    array_double_destroy(&array0);
}

TEST(array, resize)
{
    array_double array0;
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;

    EXPECT_EQ(array_double_init_copy(&array0, 4, datas), 0);
    EXPECT_EQ(array_double_size(&array0), 4);

    array_double_adjust_capacity(&array0, 9);
    EXPECT_EQ(array_double_capacity(&array0), 9);
    EXPECT_EQ(array_double_available(&array0), 5);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(ARRAY(array0)[i], datas[i]);
    }

    array_double_resize(&array0, 100);
    EXPECT_EQ(array_double_size(&array0), 100);
    EXPECT_GT(array_double_capacity(&array0), 100);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(ARRAY(array0)[i], datas[i]);
    }

    array_double_clear(&array0);
    EXPECT_EQ(array_double_size(&array0), 0);


    array_double_destroy(&array0);
}

TEST(array, find)
{
    array_double array0;
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;

    EXPECT_EQ(array_double_init_copy(&array0, 4, datas), 0);
    EXPECT_EQ(array_double_size(&array0), 4);
    EXPECT_GT(array_double_capacity(&array0), 0);

    double *ptr = array_double_find(&array0, datas[3]);
    int idx = array_double_find_idx(&array0, datas[3]);
    EXPECT_EQ(ptr, &(ARRAY(array0)[idx]));
    EXPECT_EQ(idx, 3);

    double pi = 3.1415926;
    ptr = array_double_ptr_find(&array0, &pi);
    idx = array_double_ptr_find_idx(&array0, &pi);
    EXPECT_EQ(NULL, ptr);
    EXPECT_EQ(-1, idx);

    pi = 3.2;
    ptr = array_double_ptr_find(&array0, &pi);
    idx = array_double_ptr_find_idx(&array0, &pi);
    EXPECT_EQ(ptr, &(ARRAY(array0)[idx]));
    EXPECT_EQ(idx, 1);

    array_double_destroy(&array0);
}

TEST(array, insert)
{
    array_double array0;
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;

    EXPECT_EQ(array_double_init_copy(&array0, 4, datas), 0);
    EXPECT_EQ(array_double_size(&array0), 4);
    EXPECT_GT(array_double_capacity(&array0), 0);

    double pi = 3.1415926;
    array_double_ptr_insert(&array0, 2, &pi);
    EXPECT_EQ(array_double_size(&array0), 5);
    EXPECT_EQ(ARRAY(array0)[0], datas[0]);
    EXPECT_EQ(ARRAY(array0)[1], datas[1]);
    EXPECT_EQ(ARRAY(array0)[2], 3.1415926);
    EXPECT_EQ(ARRAY(array0)[3], datas[2]);
    EXPECT_EQ(ARRAY(array0)[4], datas[3]);

    array_double_insert_section(&array0, 2, datas, 4);
    EXPECT_EQ(array_double_size(&array0), 9);
    EXPECT_EQ(ARRAY(array0)[0], datas[0]);
    EXPECT_EQ(ARRAY(array0)[1], datas[1]);
    for (int i = 0; i < 4; i++)
        EXPECT_EQ(ARRAY(array0)[2 + i], datas[i]);

    EXPECT_EQ(ARRAY(array0)[6], 3.1415926);
    EXPECT_EQ(ARRAY(array0)[7], datas[2]);
    EXPECT_EQ(ARRAY(array0)[8], datas[3]);

    EXPECT_EQ(array_double_insert(&array0, 10, 10), 1);

    for (int i = 9; i < 64; i++)
        array_double_insert(&array0, i, i);

    for (int i = 9; i < 64; i++)
        EXPECT_EQ(ARRAY(array0)[i], i);


    array_double_destroy(&array0);
}

TEST(array, remove)
{
    array_double array0;
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;

    EXPECT_EQ(array_double_init_copy(&array0, 4, datas), 0);
    EXPECT_EQ(array_double_size(&array0), 4);
    EXPECT_GT(array_double_capacity(&array0), 0);

    array_double_insert(&array0, 2, 3.1415926);
    EXPECT_EQ(array_double_size(&array0), 5);

    array_double_remove(&array0, 2);
    EXPECT_EQ(array_double_size(&array0), 4);
    EXPECT_EQ(ARRAY(array0)[0], datas[0]);
    EXPECT_EQ(ARRAY(array0)[1], datas[1]);
    EXPECT_EQ(ARRAY(array0)[2], datas[2]);
    EXPECT_EQ(ARRAY(array0)[3], datas[3]);

    array_double_insert_section(&array0, 2, datas, 4);
    EXPECT_EQ(array_double_size(&array0), 8);

    array_double_remove_section(&array0, 2, 2+4);
    EXPECT_EQ(array_double_size(&array0), 4);
    EXPECT_EQ(ARRAY(array0)[0], datas[0]);
    EXPECT_EQ(ARRAY(array0)[1], datas[1]);
    EXPECT_EQ(ARRAY(array0)[2], datas[2]);
    EXPECT_EQ(ARRAY(array0)[3], datas[3]);

    array_double_insert_section(&array0, 2, datas, 4);
    EXPECT_EQ(array_double_size(&array0), 8);
    EXPECT_EQ(array_double_remove_section(&array0, 6, 2), 1);
    EXPECT_EQ(array_double_remove(&array0, 8), 2);

    array_double_destroy(&array0);
}

TEST(array, stack)
{
    array_double array0;

    EXPECT_EQ(array_double_init(&array0, 0), 0);
    EXPECT_EQ(array_double_size(&array0), 0);
    EXPECT_TRUE(array_double_empty(&array0));
    EXPECT_FALSE(array_double_full(&array0));
    EXPECT_GT(array_double_capacity(&array0), 0);
    EXPECT_EQ(array_double_available(&array0), 1);

    for (int i = 0; i < 5; i++) {
        array_double_push(&array0, 1.1 + i);
        EXPECT_EQ(array_double_size(&array0), 1 + i);
        EXPECT_EQ(ARRAY(array0)[i], 1.1 + i);
    }
    EXPECT_EQ(array_double_size(&array0), 5);

    double tmp;
    for (int i = 5; i > 0; i--) {
        array_double_pop(&array0, &tmp);
        EXPECT_EQ(array_double_size(&array0), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(array_double_size(&array0), 0);

    for (int i = 0; i < 5; i++) {
        array_double_ptr_push(&array0, &tmp);
        EXPECT_EQ(array_double_size(&array0), 1 + i);
        EXPECT_EQ(ARRAY(array0)[i], 1.1 + i);
        tmp += 1;
    }
    EXPECT_EQ(array_double_size(&array0), 5);

    for (int i = 5; i > 0; i--) {
        array_double_pop(&array0, &tmp);
        EXPECT_EQ(array_double_size(&array0), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(array_double_size(&array0), 0);
    EXPECT_EQ(array_double_pop(&array0, &tmp), 1);

    array_double_destroy(&array0);
}




