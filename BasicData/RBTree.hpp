#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <RBTreeNode.hpp>
#include <BinaryTree.hpp>

/*
 * RBTree - 红黑树
 *
 * 1. 每个节点不是黑色就是红色
 * 2. 根节点是黑色
 * 3. 每个叶子节点(NIL)都是黑色
 * 4. 如果一个节点是红色,那么它的两个孩子都是黑色
 *    ==> 对于一个节点,如果有一个孩子是红色,那么它一定是黑色
 * 5. 对于每个节点,从该节点到其叶子后代节点的所有简单路径上具有相同数目的黑节点
 */
template <class T>
class RBTree : public BinaryTree<T> {
    private:
    public:
        RBTree() : BinaryTree<T>(), mNum(0) {}
        RBTree(RBTreeNode<T> *root) : BinaryTree<T>(root), mNum(0) { }
    public:
        RBTreeNode<T> * root() { return (RBTreeNode<T>*)this->mRoot; }
    private:
        /*
         *       y                          x
         *      / \     left_rotate @x     / \
         *     x   c  <-----------------  a   y
         *    / \     ----------------->     / \
         *   a   b     right_rotate @y      b   c 
         */
        void left_rotate(RBTreeNode<T> * x) {
            RBTreeNode<T> *y = x->right();
            RBTreeNode<T> *b = y->left();

            x->r = b;
            if (NULL != b)
                b->p = x;

            y->p = x->p;
            if (NULL == x->p)
                this->mRoot = y;
            else if (x == x->p->l)
                x->p->l = y;
            else
                x->p->r = y;

            y->l = x;
            x->p = y;
        }

        void right_rotate(RBTreeNode<T> * y) {
            RBTreeNode<T> *x = y->left();
            RBTreeNode<T> *b = x->right();

            y->l = b;
            if (NULL != b)
                b->p = y;

            x->p = y->p;
            if (NULL == y->p)
                this->mRoot = x;
            else if (y == y->p->l)
                y->p->l = x;
            else
                y->p->r = x;

            x->r = y;
            y->p = x;
        }
        /*
         * insert_fixup - 插入节点后,修复红黑树属性
         */
        void insert_fixup(RBTreeNode<T> * n) {
            RBTreeNode<T> *p, *g, *u;

            while (true) {
                p = n->parent();
                g = p->parent();

                if (RBNodeColor::RED != p->get_color())
                    break;

                if (p == g->left()) {
                    u = g->right();
                    if (RBNodeColor::RED == u->get_color()) {
                        /*
                         * Case 1 - node's uncle is red (color flips).
                         *
                         *       G            g
                         *      / \          / \
                         *     p   u  -->   P   U
                         *    /            /
                         *   n            n
                         *
                         * However, since g's parent might be red, and
                         * 4) does not allow this, we need to recurse
                         * at g.
                         */
                        p->color = RBNodeColor::BLK;
                        u->color = RBNodeColor::BLK;
                        g->color = RBNodeColor::RED;
                        n = g;
                    } else {
                        /*
                         * Case 2 - node's uncle is black and node is
                         * the parent's right child (left rotate at parent).
                         *
                         *      G             G
                         *     / \           / \
                         *    p   U  -->    n   U
                         *     \           /
                         *      n         p
                         *
                         * This still leaves us in violation of 4), the
                         * continuation into Case 3 will fix that.
                         */
                        if (n == p->right()) {
                            n = p;
                            left_rotate(n);
                        }
                        /*
                         * Case 3 - node's uncle is black and node is
                         * the parent's left child (right rotate at gparent).
                         *
                         *        G           P
                         *       / \         / \
                         *      p   U  -->  n   g
                         *     /                 \
                         *    n                   U
                         */
                        p->color = RBNodeColor::BLK;
                        g->color = RBNodeColor::RED;
                        right_rotate(g);
                    }
                } else {
                    u = g->left();
                    if (RBNodeColor::RED == u->get_color()) {
                        /*
                         * Case 1 - node's uncle is red (color flips).
                         *
                         *       G            g
                         *      / \          / \
                         *     u   p  -->   U   P
                         *          \            \ 
                         *           n            n
                         *
                         * However, since g's parent might be red, and
                         * 4) does not allow this, we need to recurse
                         * at g.
                         */
                        p->color = RBNodeColor::BLK;
                        u->color = RBNodeColor::BLK;
                        g->color = RBNodeColor::RED;
                        n = g;
                    } else {
                        /*
                         * Case 2 - node's uncle is black and node is
                         * the parent's left child (right rotate at parent).
                         *
                         *      G             G
                         *     / \           / \
                         *    U   p  -->    U   n
                         *       /               \ 
                         *      n                 p
                         *
                         * This still leaves us in violation of 4), the
                         * continuation into Case 3 will fix that.
                         */
                        if (n == p->left()) {
                            n = p;
                            right_rotate(n);
                        }
                        /*
                         * Case 3 - node's uncle is black and node is
                         * the parent's right child (left rotate at gparent).
                         *
                         *        G           P
                         *       / \         / \
                         *      U   p  -->  g   n
                         *           \     /
                         *            n   U
                         */
                        p->color = RBNodeColor::BLK;
                        g->color = RBNodeColor::RED;
                        left_rotate(g);
                    }
                }
            }
            RBTreeNode<T> *root = (RBTreeNode<T>*)(this->mRoot);
            root->color = RBNodeColor::BLK;
        }
        /*
         * remove_fixup - 移除节点后修复红黑树属性
         */
        void remove_fixup(RBTreeNode<T> *x, RBTreeNode<T> *p) {
            RBTreeNode<T> *w;
            while (root() != x && x->get_color() == RBNodeColor::BLK) {
                if (x == p->left()) {
                    w = p->right();
                    if (RBNodeColor::RED == w->get_color()) {
                        /*
                         * case1: P           W
                         *       / \         / \
                         *      X   w  -->  p   D
                         *         / \     / \
                         *        C   D   X   C(w)
                         */
                        w->set_color(RBNodeColor::BLK); 
                        p->set_color(RBNodeColor::RED);
                        left_rotate(p);
                        w = p->right();
                    }

                    if (RBNodeColor::BLK == w->left()->get_color() &&
                        RBNodeColor::BLK == w->right()->get_color()) {
                        /*
                         * case2: p           p(x)
                         *       / \         / \
                         *      X   W  -->  X   w
                         *         / \         / \
                         *        C   D       C   D 
                         */
                        w->set_color(RBNodeColor::RED);
                        x = p;
                    } else {
                        /*
                         * case3: p           p
                         *       / \         / \
                         *      X   W  -->  X   C(w)
                         *         / \           \
                         *        c   D           w 
                         *                         \
                         *                          D
                         */
                        if (RBNodeColor::BLK == w->right()->get_color()) {
                            w->left()->set_color(RBNodeColor::BLK);
                            w->set_color(RBNodeColor::RED);
                            right_rotate(w);
                            w = p->right();
                        }
                        /*
                         * case4: p           w
                         *       / \         / \
                         *      X   W  -->  P   D
                         *         / \     / \
                         *        c   d   X   c 
                         */
                        w->set_color(p->get_color());
                        p->set_color(RBNodeColor::BLK);
                        w->right()->set_color(RBNodeColor::BLK);
                        left_rotate(p);
                        x = root();
                    }
                } else {
                    w = p->left();
                    if (RBNodeColor::RED == w->get_color()) {
                        /*
                         * case1: P           W
                         *       / \         / \
                         *      w   X  -->  C   p
                         *     / \             / \
                         *    C   D           D(w)X 
                         */
                        w->set_color(RBNodeColor::BLK); 
                        p->set_color(RBNodeColor::RED);
                        right_rotate(p);
                        w = p->left();
                    }

                    if (RBNodeColor::BLK == w->left()->get_color() &&
                        RBNodeColor::BLK == w->right()->get_color()) {
                        /*
                         * case2: p           p(x)
                         *       / \         / \
                         *      W   X  -->  w   X
                         *     / \         / \
                         *    C   D       C   D 
                         */
                        w->set_color(RBNodeColor::RED);
                        x = p;
                    } else {
                        /*
                         * case3: p           p
                         *       / \         / \
                         *      W   X  -->  D   X
                         *     / \         /
                         *    C   d       w 
                         *               /
                         *              C
                         */
                        if (RBNodeColor::BLK == w->left()->get_color()) {
                            w->right()->set_color(RBNodeColor::BLK);
                            w->set_color(RBNodeColor::RED);
                            left_rotate(w);
                            w = p->left();
                        }
                        /*
                         * case4: p           w
                         *       / \         / \
                         *      W   X  -->  C   P
                         *     / \             / \ 
                         *    c   d           d   X
                         */
                        w->set_color(p->get_color());
                        p->set_color(RBNodeColor::BLK);
                        w->left()->set_color(RBNodeColor::BLK);
                        right_rotate(p);
                        x = root();
                    }
                }
            }
            x->set_color(RBNodeColor::BLK);
        }
    public:
        RBTreeNode<T> * insert(T const & data) {
            RBTreeNode<T> *re = new RBTreeNode<T>(data);
            re->color = RBNodeColor::RED;

            BinaryTree<T>::insert(re);

            insert_fixup(re);

            mNum++;
            return re;
        }

        RBTreeNode<T> * find(T const & data) {
            RBTreeNode<T> *re = (RBTreeNode<T>*)BinaryTree<T>::find(data);
            return re;
        }

        void remove(RBTreeNode<T> * node) {
            RBTreeNode<T> *n, *x, *xp;

            n = node;
            RBNodeColor nc = n->color;

            if (NULL == node->l) {
                x = node->right();
                this->replace_subtree(node, node->r);
                xp = node->parent();
            } else if (NULL == node->r) {
                x = node->left();
                this->replace_subtree(node, node->l);
                xp = node->parent();
            } else {
                n = (RBTreeNode<T>*)node->r->subtree_min_node();
                nc = n->color;
                x = n->right();
                if (node == n->p)
                    xp = n;
                else {
                    this->replace_subtree(n, n->r);
                    xp = n->parent();
                    n->r = node->r;
                    n->r->p = n;
                }
                this->replace_subtree(node, n);
                n->l = node->l;
                n->l->p = n;
                n->color = node->color;
            }

            if (RBNodeColor::BLK == nc)
                remove_fixup(x, xp);
            delete node;
            mNum--;
        }

        void remove(T const & data) { remove(find(data)); }

        int size() const { return mNum; }
    private:
        int mNum;
};

#endif

