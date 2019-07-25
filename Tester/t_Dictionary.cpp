#include <gtest/gtest.h>
#include <DictionaryNode.hpp>
#include <Dictionary.hpp>

#include <iostream>

TEST(DicNodeBase, init)
{
    DicNodeBase<char> node;

    node = 'a';
    EXPECT_EQ('a', node.key);

    char value = node;
    EXPECT_EQ('a', value);

    char &value2 = node;
    value2 = 'b';
    EXPECT_EQ('b', node);

    DicNodeBase<char> const node1('c');
    char const &value3 = node1;
    EXPECT_EQ('c', value3);
}

TEST(DicNodeBase, add_remove)
{
    DicNodeBase<char> node('a');
    EXPECT_EQ('a', node.key);

    DicNodeBase<char> *b = node.add_child(new DicNodeBase<char>('b'));
    EXPECT_EQ('b', *b);
    EXPECT_EQ(1, b->depth);

    DicNodeBase<char> *c = new DicNodeBase<char>('b');
    DicNodeBase<char> *d = node.add_child(c);
    EXPECT_EQ(NULL, d);

    c = node.add_child(new DicNodeBase<char>('c'));
    EXPECT_EQ('c', *c);

    EXPECT_TRUE(node.remove_child('b'));
    EXPECT_FALSE(node.remove_child('b'));

    b = node.find_child('b');
    EXPECT_EQ(NULL, b);

    c = node.find_child('c');
    EXPECT_EQ('c', *c);
}

TEST(DicNodeBase, trace_back)
{
    DicNodeBase<int> node('d');
    DicNodeBase<int> *p;
    
    p = node.add_child(new DicNodeBase<int>('o'));
    p = p->add_child(new DicNodeBase<int>('u'));
    p = p->add_child(new DicNodeBase<int>('n'));
    p = p->add_child(new DicNodeBase<int>('i'));
    p = p->add_child(new DicNodeBase<int>('w'));
    p = p->add_child(new DicNodeBase<int>('a'));
    p = p->add_child(new DicNodeBase<int>('n'));
    EXPECT_EQ('n', *p);
    EXPECT_EQ(7, p->depth);

    int douniwan[9];
    std::string oracle("douniwan");
    EXPECT_EQ(7, p->trace_back(douniwan, 7));
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(oracle[i], douniwan[i]);

}

TEST(DicBase, insert_find_remove)
{
    DicBase<char, double> dic;
    DicEndNode<char, double> *p, *p1;

    std::string oracle("douniwan");
    p = dic.insert(1.41421, oracle.c_str(), oracle.size(), '\0');
    EXPECT_EQ('\0', *p);
    EXPECT_EQ(1.41421, p->value);
    EXPECT_EQ(8, p->depth);

    char douniwan[9];
    EXPECT_EQ(8, p->trace_back(douniwan, 8));
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(oracle[i], douniwan[i]);

    std::string oracle1("bienao");
    p1 = dic.insert(3.1415926, oracle1.c_str(), oracle1.size(), '\0');
    EXPECT_EQ('\0', *p1);
    EXPECT_EQ(3.1415926, p1->value);
    EXPECT_EQ(6, p1->depth);
    EXPECT_EQ(6, p1->trace_back(douniwan, 8));
    for (int i = 0; i < 7; i++)
        EXPECT_EQ(oracle1[i], douniwan[i]);

    std::string oracle2("hehe");
    EXPECT_EQ(p, dic.find(oracle.c_str(), oracle.size(), '\0'));
    EXPECT_EQ(p1, dic.find(oracle1.c_str(), oracle1.size(), '\0'));
    EXPECT_EQ(NULL, dic.find(oracle2.c_str(), oracle2.size(), '\0'));

    dic.remove(oracle.c_str(), oracle.size(), '\0');
    EXPECT_EQ(NULL, dic.find(oracle.c_str(), oracle.size(), '\0'));

    std::string oracle3("逗你玩");
    char tmp[50];
    p = dic.insert(1.767, oracle3.c_str(), oracle3.size(), '\0');
    p->trace_back(tmp, 50);
    std::cout << tmp << std::endl;
}

TEST(Dictionary_char, insert_find_remove)
{
    Dictionary<char, double> dic; 
    DicEndNode<char, double> *p, *p1;

    std::string oracle("douniwan");
    p = dic.insert(oracle, 1.41421);
    EXPECT_EQ('\0', *p);
    EXPECT_EQ(1.41421, p->value);
    EXPECT_EQ(8, p->depth);

    char douniwan[9];
    EXPECT_EQ(8, p->trace_back(douniwan, 8));
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(oracle[i], douniwan[i]);

    std::string oracle1("bienao");
    p1 = dic.insert(oracle1, 3.1415926);
    EXPECT_EQ('\0', *p1);
    EXPECT_EQ(3.1415926, p1->value);
    EXPECT_EQ(6, p1->depth);
    EXPECT_EQ(6, p1->trace_back(douniwan, 8));
    for (int i = 0; i < 7; i++)
        EXPECT_EQ(oracle1[i], douniwan[i]);

    std::string oracle2("hehe");
    EXPECT_EQ(p, dic.find(oracle));
    EXPECT_EQ(p1, dic.find(oracle1));
    EXPECT_EQ(NULL, dic.find(oracle2));

    dic.remove(oracle);
    EXPECT_EQ(NULL, dic.find(oracle));

    std::string oracle3("逗你玩");
    char tmp[50];
    p = dic.insert(oracle3, 1.767);
    p->trace_back(tmp, 50);
    std::cout << tmp << std::endl;

    /*
    for (Dictionary<char, double>::PreOrderIterator it(dic); NULL != it; ++it) {
        std::cout << *it << std::endl;
    }

    for (Dictionary<char, double>::PostOrderIterator it(dic); NULL != it; ++it) {
        std::cout << *it << std::endl;
    }

    for (Dictionary<char, double>::DepthFirstIterator it(dic); NULL != it; ++it) {
        std::cout << *it << std::endl;
    }

    for (Dictionary<char, double>::BreadthFirstIterator it(dic); NULL != it; ++it) {
        std::cout << *it << std::endl;
    }
    */
}




