#include <gtest/gtest.h>
#include <DataArray.hpp>

TEST(DataArray, init)
{
    DataArray<double> *pArray = new DataArray<double>();
    EXPECT_EQ(pArray->size(), 0);
    EXPECT_EQ(pArray->capacity(), 0);
    EXPECT_TRUE(pArray->empty());
    EXPECT_TRUE(pArray->full());
    delete pArray;

    pArray = new DataArray<double>(4);
    EXPECT_EQ(pArray->size(), 4);
    delete pArray;

    // 初始赋值
    double value[9];
    for (int i = 0; i < 9; i++)
        value[i] = 3.14 * i;
    pArray = new DataArray<double>(value, 9);
    EXPECT_EQ(pArray->size(), 9);
    for (int i = 0; i < 9; i++)
        EXPECT_EQ((*pArray)[i], value[i]);
    value[5] = 101.1;
    EXPECT_NE((*pArray)[5], value[5]);

    // 拷贝构造
    DataArray<double> array = *pArray;
    EXPECT_EQ(pArray->size(), 9);
    for (int i = 0; i < 9; i++)
        EXPECT_EQ((*pArray)[i], array[i]);
    array[5] = 101.1;
    EXPECT_NE((*pArray)[5], array[5]);
    delete pArray;
}

TEST(DataArray, resize)
{
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;
    DataArray<double> array(datas, 4);
    EXPECT_EQ(array.size(), 4);

    array.adjust_capacity(10);
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 10);
    EXPECT_EQ(array.available(), 6);
    for (int i = 0; i < 4; i++)
        EXPECT_EQ(array[i], datas[i]);

    EXPECT_EQ(array.adjust_capacity(3), 1);
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 10);

    EXPECT_EQ(array.adjust_capacity(10), 0);
    EXPECT_EQ(array.size(), 4);

    EXPECT_EQ(array.resize(3), 0);
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 10);

    array.clear();
    EXPECT_EQ(array.size(), 0);

}

TEST(DataArray, find)
{
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;
    DataArray<double> array(datas, 4);
    EXPECT_EQ(array.size(), 4);

    double *ptr = array.find(datas[3]);
    int idx = array.find_idx(datas[3]);
    EXPECT_EQ(ptr, &(array[idx]));
    EXPECT_EQ(idx, 3);

    EXPECT_TRUE(array.find(1.2));
    EXPECT_FALSE(array.find(3.14));
}

TEST(DataArray, insert)
{
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;
    DataArray<double> array(datas, 4);
    EXPECT_EQ(array.size(), 4);

    double pi = 3.1415926;
    array.insert(2, pi);
    EXPECT_EQ(array.size(), 5);
    EXPECT_EQ(array[0], datas[0]);
    EXPECT_EQ(array[1], datas[1]);
    EXPECT_EQ(array[2], pi);
    EXPECT_EQ(array[3], datas[2]);
    EXPECT_EQ(array[4], datas[3]);

    array.insert(2, datas, 4);
    EXPECT_EQ(array.size(), 9);
    EXPECT_EQ(array[0], datas[0]);
    EXPECT_EQ(array[1], datas[1]);
    for (int i = 0; i < 4; i++)
        EXPECT_EQ(array[2 + i], datas[i]);

    EXPECT_EQ(array[6], 3.1415926);
    EXPECT_EQ(array[7], datas[2]);
    EXPECT_EQ(array[8], datas[3]);

    EXPECT_EQ(array.insert(10, 10), 1);

    for (int i = 9; i < 64; i++)
        array.insert(i, i);

    for (int i = 9; i < 64; i++)
        EXPECT_EQ(array[i], i);
}

TEST(DataArray, remove)
{
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;
    DataArray<double> array(datas, 4);
    EXPECT_EQ(array.size(), 4);

    double pi = 3.1415926;
    array.insert(2, pi);
    EXPECT_EQ(array.size(), 5);

    array.remove(2);
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array[0], datas[0]);
    EXPECT_EQ(array[1], datas[1]);
    EXPECT_EQ(array[2], datas[2]);
    EXPECT_EQ(array[3], datas[3]);

    array.insert(2, datas, 4);
    EXPECT_EQ(array.size(), 8);

    array.remove(2, 2+4);
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array[0], datas[0]);
    EXPECT_EQ(array[1], datas[1]);
    EXPECT_EQ(array[2], datas[2]);
    EXPECT_EQ(array[3], datas[3]);

    array.insert(2, datas, 4);
    EXPECT_EQ(array.size(), 8);
    EXPECT_EQ(array.remove(6, 2), 1);
    EXPECT_EQ(array.remove(8), 2);
}


TEST(DataArray, stack)
{
    DataArray<double> *pArray = new DataArray<double>();
    EXPECT_EQ(pArray->size(), 0);
    EXPECT_EQ(pArray->capacity(), 0);
    EXPECT_TRUE(pArray->empty());
    EXPECT_TRUE(pArray->full());

    for (int i = 0; i < 5; i++) {
        pArray->push(1.1 + i);
        EXPECT_EQ(pArray->size(), 1 + i);
        EXPECT_EQ((*pArray)[i], 1.1 + i);
    }
    EXPECT_EQ(pArray->size(), 5);

    double tmp;
    for (int i = 5; i > 0; i--) {
        pArray->pop(tmp);
        EXPECT_EQ(pArray->size(), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(pArray->size(), 0);
    EXPECT_EQ(pArray->pop(tmp), 1);

    delete pArray;
}



