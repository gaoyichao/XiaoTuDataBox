#include <gtest/gtest.h>
#include <DataQueue.hpp>


TEST(DataQueue, init)
{
    DataQueue<double> *pQueue = new DataQueue<double>();
    EXPECT_EQ(pQueue->size(), 0);
    EXPECT_TRUE(pQueue->empty());
    EXPECT_FALSE(pQueue->full());
    EXPECT_EQ(pQueue->capacity(), 4);
    EXPECT_EQ(pQueue->available(), 4);
    delete pQueue;
}


TEST(DataQueue, push_back_pop_front)
{
    DataQueue<double> *pQueue = new DataQueue<double>();

    double tmp;
    for (int i = 0; i < 13; i++) {
        EXPECT_TRUE(pQueue->push_back(1.2 * i));
        EXPECT_EQ(pQueue->size(), i+1);
    }
    EXPECT_EQ(pQueue->size(), 13);
    EXPECT_EQ(pQueue->capacity(), 16);
    pQueue->peek_front(tmp);
    EXPECT_EQ(tmp, 0);
    pQueue->peek_back(tmp);
    EXPECT_EQ(tmp, 1.2 * 12);

    for (int i = 0; i < 11; i++) {
        EXPECT_TRUE(pQueue->pop_front(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 2);
    EXPECT_EQ(pQueue->capacity(), 16);

    for (int i = 13; i < 20; i++) {
        EXPECT_TRUE(pQueue->push_back(1.2 * i));
    }
    EXPECT_EQ(pQueue->size(), 9);
    EXPECT_EQ(pQueue->capacity(), 16);

    for (int i = 11; i < 17; i++) {
        EXPECT_TRUE(pQueue->pop_front(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 3);
    EXPECT_EQ(pQueue->capacity(), 16);

    pQueue->rearrange();
    for (int i = 17; i < 19; i++) {
        EXPECT_TRUE(pQueue->pop_front(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 1);

    for (int i = 20; i < 36; i++) {
        EXPECT_TRUE(pQueue->push_back(1.2 * i));
    }
    EXPECT_EQ(pQueue->size(), 17);
    EXPECT_EQ(pQueue->capacity(), 32);

    pQueue->rearrange();
    for (int i = 19; i < 35; i++) {
        EXPECT_TRUE(pQueue->pop_front(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 1);

    EXPECT_TRUE(pQueue->pop_front(tmp));
    EXPECT_EQ(tmp, 1.2 * 35);
    EXPECT_TRUE(pQueue->empty());

    delete pQueue;
}


TEST(DataQueue, push_front_pop_back)
{
    DataQueue<double> *pQueue = new DataQueue<double>();

    double tmp;
    for (int i = 0; i < 13; i++) {
        EXPECT_TRUE(pQueue->push_front(1.2 * i));
        EXPECT_EQ(pQueue->size(), i+1);
    }
    EXPECT_EQ(pQueue->size(), 13);
    EXPECT_EQ(pQueue->capacity(), 16);
    pQueue->peek_front(tmp);
    EXPECT_EQ(tmp, 1.2 * 12);
    pQueue->peek_back(tmp);
    EXPECT_EQ(tmp, 0);

    for (int i = 0; i < 11; i++) {
        EXPECT_TRUE(pQueue->pop_back(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 2);
    EXPECT_EQ(pQueue->capacity(), 16);

    for (int i = 13; i < 20; i++) {
        EXPECT_TRUE(pQueue->push_front(1.2 * i));
    }
    EXPECT_EQ(pQueue->size(), 9);
    EXPECT_EQ(pQueue->capacity(), 16);

    for (int i = 11; i < 17; i++) {
        EXPECT_TRUE(pQueue->pop_back(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 3);
    EXPECT_EQ(pQueue->capacity(), 16);

    pQueue->rearrange();
    for (int i = 17; i < 19; i++) {
        EXPECT_TRUE(pQueue->pop_back(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 1);

    for (int i = 20; i < 36; i++) {
        EXPECT_TRUE(pQueue->push_front(1.2 * i));
    }
    EXPECT_EQ(pQueue->size(), 17);
    EXPECT_EQ(pQueue->capacity(), 32);

    pQueue->rearrange();
    for (int i = 19; i < 35; i++) {
        EXPECT_TRUE(pQueue->pop_back(tmp));
        EXPECT_EQ(tmp, 1.2 * i);
    }
    EXPECT_EQ(pQueue->size(), 1);

    EXPECT_TRUE(pQueue->pop_back(tmp));
    EXPECT_EQ(tmp, 1.2 * 35);
    EXPECT_TRUE(pQueue->empty());

    delete pQueue;
}

TEST(DataQueue, push_back_pop_back)
{
    DataQueue<double> *pQueue = new DataQueue<double>();

    for (int i = 0; i < 5; i++) {
        pQueue->push_back(1.1 + i);
        EXPECT_EQ(pQueue->size(), 1 + i);
    }
    EXPECT_EQ(pQueue->size(), 5);

    double tmp;
    for (int i = 5; i > 0; i--) {
        pQueue->pop_back(tmp);
        EXPECT_EQ(pQueue->size(), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(pQueue->size(), 0);
    EXPECT_FALSE(pQueue->pop_back(tmp));

    delete pQueue;
}


TEST(DataQueue, push_front_pop_front)
{
    DataQueue<double> *pQueue = new DataQueue<double>();

    for (int i = 0; i < 5; i++) {
        pQueue->push_front(1.1 + i);
        EXPECT_EQ(pQueue->size(), 1 + i);
    }
    EXPECT_EQ(pQueue->size(), 5);

    double tmp;
    for (int i = 5; i > 0; i--) {
        pQueue->pop_front(tmp);
        EXPECT_EQ(pQueue->size(), i - 1);
        EXPECT_EQ(tmp, 0.1 + i);
    }
    EXPECT_EQ(pQueue->size(), 0);
    EXPECT_FALSE(pQueue->pop_front(tmp));

    delete pQueue;
}





