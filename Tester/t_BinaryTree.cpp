#include <gtest/gtest.h>
#include <BinaryTreeNode.hpp>
#include <BinaryTree.hpp>

TEST(BinaryTreeNode, init)
{
    BinaryTreeNode<double> node;

    node.key = 0.1;
    node = 1.2;
    EXPECT_EQ(1.2, node.key);

    double value = node;
    EXPECT_EQ(1.2, value);

    double &value2 = node;
    value2 = 3.3;
    EXPECT_EQ(3.3, node);

    BinaryTreeNode<double> const node1(3.1);
    double const &value3 = node1;
    EXPECT_EQ(3.1, value3);

    BinaryTreeNode<double> *pnode = NULL;
    EXPECT_EQ(NULL, pnode->parent());
    EXPECT_EQ(NULL, pnode->gparent());
    EXPECT_EQ(NULL, pnode->left());
    EXPECT_EQ(NULL, pnode->right());
}

TEST(BinaryTreeNode, update)
{
    BinaryTreeNode<double> *nodes = new BinaryTreeNode<double>[5];

    for (int i = 0; i < 5; i++)
        nodes[i] = i;

    nodes[1].update_left(&nodes[3]);
    nodes[1].update_right(&nodes[4]);
    nodes[0].update_left(&nodes[1]);
    nodes[0].update_right(&nodes[2]);

    EXPECT_EQ(&nodes[1], nodes[0].l);
    EXPECT_EQ(&nodes[2], nodes[0].r);
    EXPECT_EQ(&nodes[3], nodes[1].l);
    EXPECT_EQ(&nodes[4], nodes[1].r);
    
    EXPECT_TRUE(nodes[0].is_root());
    EXPECT_FALSE(nodes[0].is_leaf());
    EXPECT_TRUE(nodes[4].is_leaf());
    EXPECT_FALSE(nodes[4].is_root());

    delete [] nodes;
}

TEST(BinaryTree, init)
{
    BinaryTreeNode<double> *nodes = new BinaryTreeNode<double>[5];
    double oracle[5];
    int i;

    for (i = 0; i < 5; i++)
        nodes[i] = i;

    nodes[1].update_left(&nodes[3]);
    nodes[1].update_right(&nodes[4]);
    nodes[0].update_left(&nodes[1]);
    nodes[0].update_right(&nodes[2]);
   
    BinaryTree<double, false> tree(&nodes[0]);
    EXPECT_FALSE(tree.empty());

    // 先序遍历
    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 3.0;
    oracle[3] = 4.0;
    oracle[4] = 2.0;
    for (auto node = tree.preorder_traversal(); NULL != node; node = tree.preorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    // 中序遍历
    i = 0;
    oracle[0] = 3.0;
    oracle[1] = 1.0;
    oracle[2] = 4.0;
    oracle[3] = 0.0;
    oracle[4] = 2.0;
    for (auto node = tree.inorder_traversal(); NULL != node; node = tree.inorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    // 后序遍历
    i = 0;
    oracle[0] = 3.0;
    oracle[1] = 4.0;
    oracle[2] = 1.0;
    oracle[3] = 2.0;
    oracle[4] = 0.0;
    for (auto node = tree.postorder_traversal(); NULL != node; node = tree.postorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    delete [] nodes;


    BinaryTree<double, false> tree2;
    BinaryTreeNode<double> *ptrnode = tree2.postorder_traversal();
    EXPECT_EQ(NULL, ptrnode);
}

TEST(BinaryTree, traversal)
{
    BinaryTreeNode<double> *nodes = new BinaryTreeNode<double>[5];
    BinaryTreeNode<double> *nodes1 = new BinaryTreeNode<double>[5];
    double oracle[10];
    int i;

    for (i = 0; i < 5; i++) {
        nodes[i] = i;
        nodes1[i] = i;
    }

    nodes[1].update_left(&nodes[3]);
    nodes[1].update_right(&nodes[4]);
    nodes[0].update_left(&nodes[1]);
    nodes[0].update_right(&nodes[2]);

    nodes1[1].update_left(&nodes1[3]);
    nodes1[1].update_right(&nodes1[4]);
    nodes1[0].update_left(&nodes1[1]);
    nodes1[0].update_right(&nodes1[2]);
   
    nodes[2].update_left(&nodes1[0]);

    BinaryTree<double, false> tree(&nodes[0]);

    // 先序遍历
    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 3.0;
    oracle[3] = 4.0;
    oracle[4] = 2.0;
    oracle[5] = 0.0;
    oracle[6] = 1.0;
    oracle[7] = 3.0;
    oracle[8] = 4.0;
    oracle[9] = 2.0;
    for (auto node = tree.preorder_traversal(); NULL != node; node = tree.preorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    // 中序遍历
    i = 0;
    oracle[0] = 3.0;
    oracle[1] = 1.0;
    oracle[2] = 4.0;
    oracle[3] = 0.0;
    oracle[4] = 3.0;
    oracle[5] = 1.0;
    oracle[6] = 4.0;
    oracle[7] = 0.0;
    oracle[8] = 2.0;
    oracle[9] = 2.0;
 
    for (auto node = tree.inorder_traversal(); NULL != node; node = tree.inorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    // 后序遍历
    i = 0;
    oracle[0] = 3.0;
    oracle[1] = 4.0;
    oracle[2] = 1.0;
    oracle[3] = 3.0;
    oracle[4] = 4.0;
    oracle[5] = 1.0;
    oracle[6] = 2.0;
    oracle[7] = 0.0;
    oracle[8] = 2.0;
    oracle[9] = 0.0;
 
    for (auto node = tree.postorder_traversal(); NULL != node; node = tree.postorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    delete [] nodes;
    delete [] nodes1;
}

TEST(BinaryTree, replace_subtree)
{
    BinaryTreeNode<double> *nodes = new BinaryTreeNode<double>[5];
    BinaryTreeNode<double> *nodes1 = new BinaryTreeNode<double>[5];
    BinaryTreeNode<double> *nodes2 = new BinaryTreeNode<double>[5];
    double oracle[10];
    int i;

    for (i = 0; i < 5; i++) {
        nodes[i] = i;
        nodes1[i] = i;
        nodes2[i] = i + 10;
    }

    nodes[1].update_left(&nodes[3]);
    nodes[1].update_right(&nodes[4]);
    nodes[0].update_left(&nodes[1]);
    nodes[0].update_right(&nodes[2]);

    nodes1[1].update_left(&nodes1[3]);
    nodes1[1].update_right(&nodes1[4]);
    nodes1[0].update_left(&nodes1[1]);
    nodes1[0].update_right(&nodes1[2]);

    nodes2[1].update_left(&nodes2[3]);
    nodes2[1].update_right(&nodes2[4]);
    nodes2[0].update_left(&nodes2[1]);
    nodes2[0].update_right(&nodes2[2]);

    nodes[2].update_left(&nodes1[0]);

    BinaryTree<double, false> tree(&nodes[0]);
    tree.replace_subtree(&nodes1[0], &nodes2[0]);

    // 先序遍历
    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 3.0;
    oracle[3] = 4.0;
    oracle[4] = 2.0;
    oracle[5] = 10.0;
    oracle[6] = 11.0;
    oracle[7] = 13.0;
    oracle[8] = 14.0;
    oracle[9] = 12.0;
    for (auto node = tree.preorder_traversal(); NULL != node; node = tree.preorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    // 中序遍历
    i = 0;
    oracle[0] = 3.0;
    oracle[1] = 1.0;
    oracle[2] = 4.0;
    oracle[3] = 0.0;
    oracle[4] = 13.0;
    oracle[5] = 11.0;
    oracle[6] = 14.0;
    oracle[7] = 10.0;
    oracle[8] = 12.0;
    oracle[9] = 2.0;
 
    for (auto node = tree.inorder_traversal(); NULL != node; node = tree.inorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    // 后序遍历
    i = 0;
    oracle[0] = 3.0;
    oracle[1] = 4.0;
    oracle[2] = 1.0;
    oracle[3] = 13.0;
    oracle[4] = 14.0;
    oracle[5] = 11.0;
    oracle[6] = 12.0;
    oracle[7] = 10.0;
    oracle[8] = 2.0;
    oracle[9] = 0.0;
    for (auto node = tree.postorder_traversal(); NULL != node; node = tree.postorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    delete [] nodes;
    delete [] nodes1;
}


TEST(BinaryTree, insert)
{
    BinaryTree<double> *tree;
    BinaryTreeNode<double> * node;

    tree = new BinaryTree<double>;
    tree->insert(2.0);
    node = tree->minimum();
    EXPECT_EQ(2.0, *node);
    tree->remove(2.0);
    EXPECT_TRUE(tree->empty());
    tree->insert(2.0);
    delete tree;

    tree = new BinaryTree<double>;
    int i;
    double oracle[5];

    tree->insert(2.0);
    tree->insert(4.0);
    tree->insert(0.0);
    tree->insert(1.0);
    tree->insert(3.0);

    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 2.0;
    oracle[3] = 3.0;
    oracle[4] = 4.0;
    for (node = tree->inorder_traversal(); NULL != node; node = tree->inorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    i = 0;
    oracle[0] = 1.0;
    oracle[1] = 0.0;
    oracle[2] = 3.0;
    oracle[3] = 4.0;
    oracle[4] = 2.0;
    for (node = tree->postorder_traversal(); NULL != node; node = tree->postorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    node = tree->minimum();
    EXPECT_EQ(0.0, *node);

    node = tree->maximum();
    EXPECT_EQ(4.0, *node);

    delete tree;
}

TEST(BinaryTree, min_max)
{
    BinaryTree<double> tree;
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

TEST(BinaryTree, find)
{
    BinaryTree<double> tree;
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

TEST(BinaryTree, remove)
{
    BinaryTree<double> tree;
    BinaryTreeNode<double> * node;
    int i;
    double oracle[5];

    tree.insert(2.0);
    tree.insert(4.0);
    tree.insert(0.0);
    tree.insert(1.0);
    tree.insert(3.0);

    node = tree.root_ptr();
    EXPECT_EQ(2, *node);
    tree.remove(node);

    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 3.0;
    oracle[3] = 4.0;
    for (node = tree.inorder_traversal(); NULL != node; node = tree.inorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }

    node = tree.root_ptr();
    EXPECT_EQ(3, *node);
    tree.remove(node);

    i = 0;
    oracle[0] = 0.0;
    oracle[1] = 1.0;
    oracle[2] = 4.0;
    for (node = tree.inorder_traversal(); NULL != node; node = tree.inorder_traversal()) {
        EXPECT_EQ(oracle[i], *node);
        i++;
    }
}

/*******************************************************************************************
 *
 *
 ******************************************************************************************/

TEST(BinaryPtrTree, insert)
{
    BinaryTree<double*> *tree;
    BinaryTreeNode<double*> *node;
    BinaryTreeNode<double*> *node1;

    double values[10];
    for (int i = 0; i < 10; i++)
        values[i] = 3.14 * i;

    tree = new BinaryTree<double*>;
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

    tree = new BinaryTree<double*>;
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
    for (node = tree->inorder_traversal(); NULL != node; node = tree->inorder_traversal()) {
        EXPECT_EQ(oracle[i], *(*node));
        i++;
    }

    i = 0;
    double oracle1[5];
    oracle1[0] = 2.0;
    oracle1[1] = 0.0;
    oracle1[2] = 1.0;
    oracle1[3] = 4.0;
    oracle1[4] = 3.0;
    for (node = tree->preorder_traversal(); NULL != node; node = tree->preorder_traversal()) {
        EXPECT_EQ(oracle1[i], *(*node));
        i++;
    }

    i = 0;
    oracle1[5];
    oracle1[0] = 1.0;
    oracle1[1] = 0.0;
    oracle1[2] = 3.0;
    oracle1[3] = 4.0;
    oracle1[4] = 2.0;
    for (node = tree->postorder_traversal(); NULL != node; node = tree->postorder_traversal()) {
        EXPECT_EQ(oracle1[i], *(*node));
        i++;
    }


    node = tree->minimum();
    EXPECT_EQ(0.0, *(*node));

    node = tree->maximum();
    EXPECT_EQ(4.0, *(*node));

    delete tree;
}





