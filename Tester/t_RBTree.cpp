#include <gtest/gtest.h>
#include <RBTreeNode.hpp>
#include <RBTree.hpp>

#include <iostream>

TEST(RBTreeNode, init)
{
    RBTreeNode<double> node;

    node.key = 0.1;
    node = 1.2;
    EXPECT_EQ(1.2, node.key);

    double value = node;
    EXPECT_EQ(1.2, value);

    double &value2 = node;
    value2 = 3.3;
    EXPECT_EQ(3.3, node);

    RBTreeNode<double> const node1(3.1);
    double const &value3 = node1;
    EXPECT_EQ(3.1, value3);

    RBTreeNode<double> *pnode = NULL;
    EXPECT_EQ(pnode->get_color(), RBNodeColor::BLK);

    node.color = RBNodeColor::RED;
    EXPECT_EQ((&node)->get_color(), RBNodeColor::RED);

    EXPECT_EQ(NULL, node.predecessor());
    EXPECT_EQ(NULL, node.successor());
    EXPECT_EQ(&node, node.subtree_min_node());
    EXPECT_EQ(&node, node.subtree_max_node());
}

TEST(RBTree, iterator)
{
    RBTree<double> *tree;
    BinaryTreeNode<double> * node;
    int i;
    double oracle[5];

    tree = new RBTree<double>;
    tree->insert(2.0);
    node = tree->minimum();
    EXPECT_EQ(2.0, *node);
    tree->remove(2.0);
    EXPECT_TRUE(tree->empty());
    tree->insert(2.0);

    delete tree;
}

TEST(RBTree, insert)
{
    RBTree<double> *tree;
    BinaryTreeNode<double> * node;
    int i;
    double oracle[5];

    tree = new RBTree<double>;
    tree->insert(2.0);
    node = tree->minimum();
    EXPECT_EQ(2.0, *node);
    tree->remove(2.0);
    EXPECT_TRUE(tree->empty());
    tree->insert(2.0);
    delete tree;

    tree = new RBTree<double>;
    tree->insert(2);
    tree->insert(4);
    tree->insert(0);
    tree->insert(1);
    tree->insert(3);

    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 2.0;
    oracle[3] = 3.0;
    oracle[4] = 4.0;
    for (RBTree<double>::InOrderIterator it(*tree); NULL != it; ++it) {
        EXPECT_EQ(oracle[i], *it);
        i++;
    }

    i = 0;
    oracle[0] = 1.0;
    oracle[1] = 0.0;
    oracle[2] = 3.0;
    oracle[3] = 4.0;
    oracle[4] = 2.0;
    for (RBTree<double>::PostOrderIterator it(*tree); NULL != it; ++it) {
        EXPECT_EQ(oracle[i], *it);
        i++;
    }

    node = tree->minimum();
    EXPECT_EQ(0.0, *node);

    node = tree->maximum();
    EXPECT_EQ(4.0, *node);

    for (i = 5; i < 10 ; i++)
        tree->insert(1.0 * i);

    node = tree->minimum();
    EXPECT_EQ(0.0, *node);

    i = 0;
    for (node = tree->minimum(); NULL != node; node = node->successor()) {
        EXPECT_EQ(i, *node);
        i++;
    }

    i = 10;
    for (node = tree->maximum(); NULL != node; node = node->predecessor()) {
        i--;
        EXPECT_EQ(i, *node);
    }
    delete tree;
}


TEST(RBTree, min_max)
{
    RBTree<double> tree;
    BinaryTreeNode<double> * node;
    int i;
    double oracle[5];

    tree.insert(2.0);
    tree.insert(4.0);
    tree.insert(0.0);
    tree.insert(1.0);
    tree.insert(3.0);

    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 2.0;
    oracle[3] = 3.0;
    oracle[4] = 4.0;
    for (node = tree.minimum(); NULL != node; node = node->successor()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    i = 0;
    oracle[0] = 4.0;
    oracle[1] = 3.0;
    oracle[2] = 2.0;
    oracle[3] = 1.0;
    oracle[4] = 0.0;
    for (node = tree.maximum(); NULL != node; node = node->predecessor()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }
}


TEST(RBTree, find)
{
    RBTree<double> tree;
    BinaryTreeNode<double> * node;
    int i;
    double oracle[5];

    tree.insert(2.0);
    tree.insert(4.0);
    tree.insert(0.0);
    tree.insert(1.0);
    tree.insert(3.0);

    node = tree.find(30);
    EXPECT_TRUE(NULL == node);

    node = tree.find(3);
    EXPECT_FALSE(NULL == node);
    EXPECT_EQ(3, *node);
}


TEST(RBTree, remove)
{
    RBTree<double> tree;
    BinaryTreeNode<double> * node;
    int i;
    double oracle[10];

    tree.insert(2.0);
    tree.insert(4.0);
    tree.insert(0.0);
    tree.insert(1.0);
    tree.insert(3.0);

    node = tree.root_ptr();
    EXPECT_EQ(2, *node);
    tree.remove((RBTreeNode<double>*)node);

    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 3.0;
    oracle[3] = 4.0;
    for (RBTree<double>::InOrderIterator it(tree); NULL != it; ++it) {
        EXPECT_EQ(oracle[i], *it);
        i++;
    }

    node = tree.root_ptr();
    EXPECT_EQ(3, *node);
    tree.remove((RBTreeNode<double>*)node);

    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 4.0;
    for (RBTree<double>::InOrderIterator it(tree); NULL != it; ++it) {
        EXPECT_EQ(oracle[i], *it);
        i++;
    }

    for (i = 5; i < 10; i++)
        tree.insert(i);
    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 4.0;
    oracle[3] = 5.0;
    oracle[4] = 6.0;
    oracle[5] = 7.0;
    oracle[6] = 8.0;
    oracle[7] = 9.0;
    for (RBTree<double>::InOrderIterator it(tree); NULL != it; ++it) {
        EXPECT_EQ(oracle[i], *it);
        i++;
    }
    tree.remove(9.0);
    tree.insert(19.0);
    tree.remove(8.0);
    tree.insert(28.0);

    i = 0;
    oracle[6] = 19.0;
    oracle[7] = 28.0;
    for (RBTree<double>::InOrderIterator it(tree); NULL != it; ++it) {
        EXPECT_EQ(oracle[i], *it);
        i++;
    }
    EXPECT_EQ(i, 8);
}

TEST(RBPtrTree, insert)
{
    RBTree<double*> *tree;
    BinaryTreeNode<double*> * node;
    BinaryTreeNode<double*> *node1;

    double values[10];
    for (int i = 0; i < 10; i++)
        values[i] = 3.14 * i;

    tree = new RBTree<double*>;
    EXPECT_TRUE(tree->is_search_tree());
    tree->insert(&values[2]);
    node = tree->minimum();
    EXPECT_EQ(2 * 3.14, *(*node));

    node1 = tree->find(values[2]);
    EXPECT_EQ(node1, node);

    tree->remove(2 * 3.14);
    EXPECT_TRUE(tree->empty());
    tree->insert(&values[2]);

    delete tree;

    tree = new RBTree<double*>;
    double oracle[5];
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 2.0;
    oracle[3] = 3.0;
    oracle[4] = 4.0;

    tree->insert(&oracle[2]);
    tree->insert(&oracle[4]);
    tree->insert(&oracle[0]);
    tree->insert(&oracle[1]);
    tree->insert(&oracle[3]);

    int i = 0;
    for (RBTree<double*>::InOrderIterator it(*tree); NULL != it; ++it) {
        EXPECT_EQ(oracle[i], *(*it));
        i++;
    }

    i = 0;
    double oracle1[5];
    oracle1[0] = 2.0;
    oracle1[1] = 0.0;
    oracle1[2] = 1.0;
    oracle1[3] = 4.0;
    oracle1[4] = 3.0;
    for (RBTree<double*>::PreOrderIterator it(*tree); NULL != it; ++it) {
        EXPECT_EQ(oracle1[i], *(*it));
        i++;
    }

    i = 0;
    oracle1[5];
    oracle1[0] = 1.0;
    oracle1[1] = 0.0;
    oracle1[2] = 3.0;
    oracle1[3] = 4.0;
    oracle1[4] = 2.0;
    for (RBTree<double*>::PostOrderIterator it(*tree); NULL != it; ++it) {
        EXPECT_EQ(oracle1[i], *(*it));
        i++;
    }


    node = tree->minimum();
    EXPECT_EQ(0.0, *(*node));

    node = tree->maximum();
    EXPECT_EQ(4.0, *(*node));

    delete tree;
}


