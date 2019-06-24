#include <gtest/gtest.h>
#include <DictionaryNode.hpp>
#include <Dictionary.hpp>

#include <iostream>

TEST(DictionaryNode, init)
{
    DictionaryNode<char, double> node;

    node = 'a';
    EXPECT_EQ('a', node.key);

    char value = node;
    EXPECT_EQ('a', value);

    char &value2 = node;
    value2 = 'b';
    EXPECT_EQ('b', node);

    DictionaryNode<char, double> const node1('c');
    char const &value3 = node1;
    EXPECT_EQ('c', value3);
}

TEST(DictionaryNode, add_remove)
{
    DictionaryNode<char, double> node('a');
    EXPECT_EQ('a', node.key);

    DictionaryNode<char, double> *b = node.add_child('b');
    EXPECT_EQ('b', *b);
    EXPECT_EQ(1, b->depth);

    DictionaryNode<char, double> *c = node.add_child('b');
    EXPECT_EQ(c, b);

    c = node.add_child('c');
    EXPECT_EQ('c', *c);

    EXPECT_TRUE(node.remove_child('b'));
    EXPECT_FALSE(node.remove_child('b'));

    b = node.find_child('b');
    EXPECT_EQ(NULL, b);

    c = node.find_child('c');
    EXPECT_EQ('c', *c);
}

TEST(DictionaryNode, trace_back)
{
    DictionaryNode<char, double> node('d');
    DictionaryNode<char, double> *p;
    
    p = node.add_child('o');
    p = p->add_child('u');
    p = p->add_child('n');
    p = p->add_child('i');
    p = p->add_child('w');
    p = p->add_child('a');
    p = p->add_child('n');
    EXPECT_EQ('n', *p);
    EXPECT_EQ(7, p->depth);

    char douniwan[9];
    std::string oracle("douniwan");
    EXPECT_EQ(7, p->trace_back(douniwan, 7));
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(oracle[i], douniwan[i]);

}

TEST(Dictionary, insert_find_remove)
{
    Dictionary<char, double> dic; 
    DictionaryNode<char, double> *p, *p1;

    std::string oracle("douniwan");
    p = dic.insert(oracle.c_str(), 8);
    EXPECT_EQ('n', *p);
    EXPECT_EQ(7, p->depth);

    char douniwan[9];
    EXPECT_EQ(7, p->trace_back(douniwan, 8));
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(oracle[i], douniwan[i]);

    std::string oracle1("bienao");
    p1 = dic.insert(oracle1.c_str(), 6);
    EXPECT_EQ('o', *p1);
    EXPECT_EQ(5, p1->depth);
    EXPECT_EQ(5, p1->trace_back(douniwan, 8));
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(oracle1[i], douniwan[i]);

    std::string oracle2("hehe");
    EXPECT_EQ(p, dic.find(oracle.c_str(), 8));
    EXPECT_EQ(p1, dic.find(oracle1.c_str(), 6));
    EXPECT_EQ(NULL, dic.find(oracle2.c_str(), 4));

    dic.remove(oracle.c_str(), 8);
    EXPECT_EQ(NULL, dic.find(oracle.c_str(), 8));
    EXPECT_FALSE(dic.remove(oracle1.c_str(), 2));
}


