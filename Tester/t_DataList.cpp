#include <gtest/gtest.h>
#include <DataListNode.hpp>
#include <DataList.hpp>

TEST(DataListNode, init)
{
    DataListNode<double> node;

    node.key = 0.1;
    node = 1.2;
    EXPECT_EQ(1.2, node.key);
}

TEST(DataListNode, insert_remove_swap)
{
    DataListNode<double> head(0.1);

    DataListNode<double> *n1 = head.add(0.2);
    DataListNode<double> *n2 = head.add_prev(0.3);
    EXPECT_EQ(0.2, head.data_next());
    EXPECT_EQ(0.3, head.data_prev());
    EXPECT_EQ(0.3, n1->data_next());
    EXPECT_EQ(0.1, n2->data_next());

    n2->remove();
    delete n2;
    EXPECT_EQ(0.2, head.data_next());
    EXPECT_EQ(0.2, head.data_prev());
    EXPECT_EQ(0.1, n1->data_next());

    n1->remove();
    delete n1;
    EXPECT_TRUE(head.is_sigular());

    n1 = new DataListNode<double>(0.2);
    n2 = new DataListNode<double>(0.3);
    head.add(n1);
    head.add_prev(n2);
    EXPECT_EQ(0.2, head.data_next());
    EXPECT_EQ(0.3, head.data_prev());
    EXPECT_EQ(0.3, n1->data_next());
    EXPECT_EQ(0.1, n2->data_next());

    DataListNode<double> tmp(1.3);
    replace(n1, &tmp);
    EXPECT_EQ(1.3, head.data_next());
    EXPECT_EQ(0.3, head.data_prev());
    EXPECT_EQ(0.1, n2->data_next());
    EXPECT_EQ(1.3, n2->data_prev());
    replace(n2, n1);
    EXPECT_EQ(1.3, head.data_next());
    EXPECT_EQ(0.2, head.data_prev());
    EXPECT_EQ(0.1, n1->data_next());
    EXPECT_EQ(1.3, n1->data_prev());
    replace(&tmp, n2);
    EXPECT_EQ(0.3, head.data_next());
    EXPECT_EQ(0.2, head.data_prev());
    EXPECT_EQ(0.1, n1->data_next());
    EXPECT_EQ(0.3, n1->data_prev());

    swap(n1, n2);
    EXPECT_EQ(0.2, head.data_next());
    EXPECT_EQ(0.3, head.data_prev());
    EXPECT_EQ(0.3, n1->data_next());
    EXPECT_EQ(0.1, n2->data_next());


    n2->remove();
    n1->remove();
    delete n2;
    delete n1;
}

TEST(DataList, init)
{
    DataList<double> list;
    EXPECT_TRUE(list.empty());

    DataList<double> list1(10);
    EXPECT_EQ(10, list1.size());

    double buffer[10];
    for (int i = 0; i < 10; i++)
        buffer[i] = i + 0.1;
    DataList<double> list2(buffer, 10);
    int i = 0;
    for (DataListNode<double> *ptr = list2.begin(); ptr != list2.end(); ptr = ptr->next_ptr()) {
        EXPECT_EQ(buffer[i], ptr->key);
        i++;
    }
}

TEST(DataList, find)
{
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;
    DataList<double> list(datas, 4);
    EXPECT_EQ(list.size(), 4);

    DataListNode<double> *ptr = list.find(datas[3]);
    EXPECT_EQ(ptr->key, datas[3]);

    EXPECT_TRUE(list.find(1.2));
    EXPECT_FALSE(list.find(3.14));
}


TEST(DataList, insert_remove)
{
    double datas[4];
    datas[0] = 1.2;
    datas[1] = 3.2;
    datas[2] = 5.2;
    datas[3] = 1.332;
    DataList<double> list(datas, 4);
    EXPECT_EQ(list.size(), 4);

    DataListNode<double> *ptr = list.find(datas[2]);
    EXPECT_EQ(ptr->key, datas[2]);

    ptr = list.insert(ptr, 3.14);
    EXPECT_EQ(ptr->key, 3.14);
    EXPECT_EQ(list.size(), 5);

    list.remove(ptr);
    EXPECT_EQ(list.size(), 4);

    int i = 0;
    for (DataListNode<double> *ptr = list.begin(); ptr != list.end(); ptr = ptr->next_ptr()) {
        EXPECT_EQ(datas[i], ptr->key);
        i++;
    }

}



