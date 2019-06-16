#ifndef RBTREENODE_HPP
#define RBTREENODE_HPP

#include <BinaryTreeNode.hpp>

enum RBNodeColor {
    RED = 0,
    BLK = 1
};

/*
 * RBTreeNode - 红黑树节点
 */
template <class T>
class RBTreeNode : public BinaryTreeNode<T> {
    public:
        RBTreeNode() : BinaryTreeNode<T>(), color(RBNodeColor::BLK) { }
        RBTreeNode(T const & data) : BinaryTreeNode<T>(data), color(RBNodeColor::BLK) { }

    private:
        /*
         * 屏蔽拷贝构造函数和赋值运算
         */
        RBTreeNode(RBTreeNode const &node) {}
        RBTreeNode & operator = (RBTreeNode const &node) {}

    public:
        RBTreeNode & operator = (T const &data) { this->key = data; }
        & operator T() { return this->key; }
        & operator const T() const { return this->key; }

    public:
        RBNodeColor get_color() { 
            if (NULL == this)
                return RBNodeColor::BLK;
            return color;
        }

        void set_color(RBNodeColor const & c) {
            if (NULL == this)
                return;
            color = c;
        }

        RBTreeNode * parent() {
            if (NULL == this)
                return NULL;
            return (RBTreeNode*)this->p;
        }

        RBTreeNode * left() {
            if (NULL == this)
                return NULL;
            return (RBTreeNode*)this->l;
        }

        RBTreeNode * right() {
            if (NULL == this)
                return NULL;
            return (RBTreeNode*)this->r;
        }

        RBTreeNode * gparent() {
            RBTreeNode *_p = parent();
            return _p->parent();
        }


    public:
        RBNodeColor color;
};


#endif

