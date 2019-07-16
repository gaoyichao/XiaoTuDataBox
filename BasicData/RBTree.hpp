/*****************************************************************************************
 *
 * RBTree - 红黑树
 *
 * 1. 每个节点不是黑色就是红色
 * 2. 根节点是黑色
 * 3. 每个叶子节点(NIL)都是黑色
 * 4. 如果一个节点是红色,那么它的两个孩子都是黑色
 *    ==> 对于一个节点,如果有一个孩子是红色,那么它一定是黑色
 * 5. 对于每个节点,从该节点到其叶子后代节点的所有简单路径上具有相同数目的黑节点
 *
 ****************************************************************************************/
#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <RBTreeBase.hpp>

template <class T>
class RBTree : public RBTreeBase<T> {
    public:
        RBTree() : RBTreeBase<T>(), mNum(0) {}
        RBTree(RBTreeNode<T> *root) : RBTreeBase<T>(root), mNum(0) { }
    public:
        RBTreeNode<T> * insert(T const & data) {
            RBTreeNode<T> *re = new RBTreeNode<T>(data);
            re->color = RBNodeColor::RED;

            BinaryTree<T>::insert(re);

            this->insert_fixup(re);

            mNum++;
            return re;
        }

        RBTreeNode<T> * find(T const & data) {
            RBTreeNode<T> *re = (RBTreeNode<T>*)BinaryTree<T>::find(data);
            return re;
        }

        void remove(RBTreeNode<T> * node) {
            if (NULL == node)
                return;
            ((RBTreeBase<T>*)this)->remove(node);
            mNum--;
        }

        void remove(T const & data) { remove(find(data)); }

        int size() const { return mNum; }
    private:
        int mNum;
};

template <class T>
class RBTree<T*> : public RBTreeBase<T*> {
    public:
        RBTree() : RBTreeBase<T*>(), mNum(0) {}
        RBTree(RBTreeNode<T*> *root) : RBTreeBase<T*>(root), mNum(0) { }
    public:
        RBTreeNode<T*> * insert(T * data) {
            RBTreeNode<T*> *re = new RBTreeNode<T*>(data);
            re->color = RBNodeColor::RED;

            BinaryTree<T*>::insert(re);

            this->insert_fixup(re);

            mNum++;
            return re;
        }

        RBTreeNode<T*> * find(T const & data) {
            RBTreeNode<T*> *re = (RBTreeNode<T*>*)BinaryTree<T*>::find(data);
            return re;
        }

        void remove(RBTreeNode<T*> * node) {
            if (NULL == node)
                return;
            ((RBTreeBase<T*>*)this)->remove(node);
            mNum--;
        }

        void remove(T const & data) { remove(find(data)); }

        int size() const { return mNum; }
    private:
        int mNum;
};




#endif

