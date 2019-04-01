#include <gtest/gtest.h>

#define T double 
#define TEMPLATE_TYPE(a) a ##_double
#define TEMPLATE_FUNCTION(a,b) a ##_double_## b
#include "s_array.h.h"
#include "s_array.c.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T


TEST(s_array, init)
{
    double array_buf[64];
    s_array_double array;

    EXPECT_EQ(s_array_double_init(&array, 0, array_buf, 64), 0);
    EXPECT_EQ(s_array_double_size(&array), 0);
    EXPECT_TRUE(s_array_double_empty(&array));
    EXPECT_FALSE(s_array_double_full(&array));
    EXPECT_EQ(s_array_double_capacity(&array), 64);
    EXPECT_EQ(s_array_double_available(&array), 64);

    s_array_double_clear(&array);
    EXPECT_EQ(s_array_double_size(&array), 0);
}

TEST(s_array, element)
{
    double array_buf[64];
    s_array_double array;

    EXPECT_EQ(s_array_double_init(&array, 4, array_buf, 64), 0);
    EXPECT_EQ(s_array_double_size(&array), 4);
    EXPECT_EQ(s_array_double_capacity(&array), 64);
    EXPECT_EQ(s_array_double_available(&array), 60);

    double *ptr = s_array_double_e_ptr(&array, 2);
    *ptr = 3.14;
    EXPECT_EQ(ARRAY(array)[2], 3.14);

    s_array_double_set(&array, 0, 1.414);
    EXPECT_EQ(s_array_double_e(&array, 0), 1.414);

    double tmp = 101.01;
    s_array_double_ptr_set(&array, 0, &tmp);
    EXPECT_EQ(s_array_double_e(&array, 0), tmp);


    const double *ptr1 = s_array_double_e_cptr(&array, 1);
    EXPECT_EQ(*ptr1, ARRAY(array)[1]);
}

TEST(s_array, find)
{
    double array_buf[64];
    s_array_double array;

    array_buf[0] = 1.2;
    array_buf[1] = 3.2;
    array_buf[2] = 5.2;
    array_buf[3] = 1.332;

    EXPECT_EQ(s_array_double_init(&array, 4, array_buf, 64), 0);
    EXPECT_EQ(s_array_double_size(&array), 4);
    EXPECT_EQ(s_array_double_capacity(&array), 64);

    double *ptr = s_array_double_find(&array, 1.332);
    int idx = s_array_double_find_idx(&array, 1.332);
    EXPECT_EQ(ptr, &array_buf[idx]);
    EXPECT_EQ(idx, 3);

    double pi = 3.1415926;
    ptr = s_array_double_ptr_find(&array, &pi);
    idx = s_array_double_ptr_find_idx(&array, &pi);
    EXPECT_EQ(NULL, ptr);
    EXPECT_EQ(-1, idx);

    pi = 3.2;
    ptr = s_array_double_ptr_find(&array, &pi);
    idx = s_array_double_ptr_find_idx(&array, &pi);
    EXPECT_EQ(ptr, &(ARRAY(array)[idx]));
    EXPECT_EQ(idx, 1);
}

TEST(s_array, insert)
{
    double array_buf[64];
    s_array_double array;

    double datas[4];
    datas[0] = array_buf[0] = 1.2;
    datas[1] = array_buf[1] = 3.2;
    datas[2] = array_buf[2] = 5.2;
    datas[3] = array_buf[3] = 1.332;

    EXPECT_EQ(s_array_double_init(&array, 4, array_buf, 64), 0);
    EXPECT_EQ(s_array_double_size(&array), 4);
    EXPECT_EQ(s_array_double_capacity(&array), 64);

    double pi = 3.1415926;
    s_array_double_ptr_insert(&array, 2, &pi);
    EXPECT_EQ(s_array_double_size(&array), 5);
    EXPECT_EQ(ARRAY(array)[0], datas[0]);
    EXPECT_EQ(ARRAY(array)[1], datas[1]);
    EXPECT_EQ(ARRAY(array)[2], 3.1415926);
    EXPECT_EQ(ARRAY(array)[3], datas[2]);
    EXPECT_EQ(ARRAY(array)[4], datas[3]);

    s_array_double_insert_section(&array, 2, datas, 4);
    EXPECT_EQ(s_array_double_size(&array), 9);
    EXPECT_EQ(ARRAY(array)[0], datas[0]);
    EXPECT_EQ(ARRAY(array)[1], datas[1]);
    for (int i = 0; i < 4; i++)
        EXPECT_EQ(ARRAY(array)[2 + i], datas[i]);

    EXPECT_EQ(ARRAY(array)[6], 3.1415926);
    EXPECT_EQ(ARRAY(array)[7], datas[2]);
    EXPECT_EQ(ARRAY(array)[8], datas[3]);

    EXPECT_EQ(s_array_double_insert(&array, 10, 10), 1);

    for (int i = 9; i < 64; i++)
        s_array_double_insert(&array, i, i);

    for (int i = 9; i < 64; i++)
        EXPECT_EQ(ARRAY(array)[i], i);

    EXPECT_EQ(s_array_double_insert(&array, 60, 9), 1);
}
TEST(s_array, remove)
{
    double array_buf[64];
    s_array_double array;

    double datas[4];
    datas[0] = array_buf[0] = 1.2;
    datas[1] = array_buf[1] = 3.2;
    datas[2] = array_buf[2] = 5.2;
    datas[3] = array_buf[3] = 1.332;

    EXPECT_EQ(s_array_double_init(&array, 4, array_buf, 64), 0);
    EXPECT_EQ(s_array_double_size(&array), 4);
    EXPECT_EQ(s_array_double_capacity(&array), 64);

    s_array_double_insert(&array, 2, 3.1415926);
    EXPECT_EQ(s_array_double_size(&array), 5);

    s_array_double_remove(&array, 2);
    EXPECT_EQ(s_array_double_size(&array), 4);
    EXPECT_EQ(ARRAY(array)[0], datas[0]);
    EXPECT_EQ(ARRAY(array)[1], datas[1]);
    EXPECT_EQ(ARRAY(array)[2], datas[2]);
    EXPECT_EQ(ARRAY(array)[3], datas[3]);

    s_array_double_insert_section(&array, 2, datas, 4);
    EXPECT_EQ(s_array_double_size(&array), 8);

    s_array_double_remove_section(&array, 2, 2+4);
    EXPECT_EQ(s_array_double_size(&array), 4);
    EXPECT_EQ(ARRAY(array)[0], datas[0]);
    EXPECT_EQ(ARRAY(array)[1], datas[1]);
    EXPECT_EQ(ARRAY(array)[2], datas[2]);
    EXPECT_EQ(ARRAY(array)[3], datas[3]);

    s_array_double_insert_section(&array, 2, datas, 4);
    EXPECT_EQ(s_array_double_size(&array), 8);
    EXPECT_EQ(s_array_double_remove_section(&array, 6, 2), 1);
    EXPECT_EQ(s_array_double_remove(&array, 8), 2);


}

TEST(s_array, stack)
{
    double array_buf[5];
    s_array_double array;

    EXPECT_EQ(s_array_double_init(&array, 0, array_buf, 5), 0);

    for (int i = 0; i < 5; i++) {
        s_array_double_push(&array, 1.1 + i);
        EXPECT_EQ(s_array_double_size(&array), 1 + i);
        EXPECT_EQ(ARRAY(array)[i], 1.1 + i);
    }
    EXPECT_EQ(s_array_double_size(&array), 5);
    EXPECT_EQ(s_array_double_push(&array, 3.14), 1);

    double tmp;
    for (int i = 5; i > 0; i--) {
        s_array_double_pop(&array, &tmp);
        EXPECT_EQ(s_array_double_size(&array), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(s_array_double_size(&array), 0);
    EXPECT_EQ(s_array_double_pop(&array, &tmp), 1);

    for (int i = 0; i < 5; i++) {
        s_array_double_ptr_push(&array, &tmp);
        EXPECT_EQ(s_array_double_size(&array), 1 + i);
        EXPECT_EQ(ARRAY(array)[i], 1.1 + i);
        tmp += 1;
    }
    EXPECT_EQ(s_array_double_size(&array), 5);
    EXPECT_EQ(s_array_double_push(&array, 3.14), 1);

    for (int i = 5; i > 0; i--) {
        s_array_double_pop(&array, &tmp);
        EXPECT_EQ(s_array_double_size(&array), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(s_array_double_size(&array), 0);
    EXPECT_EQ(s_array_double_pop(&array, &tmp), 1);


}




