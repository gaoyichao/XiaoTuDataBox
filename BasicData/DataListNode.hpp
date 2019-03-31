#ifndef DATA_LIST_NODE_HPP
#define DATA_LIST_NODE_HPP

#include <iostream>

template <class T> class DataList;

template <class T>
class DataListNode {
    friend class DataList<T>;
    public:
        DataListNode() : prev(this), next(this) { }
        DataListNode(T const & data) : prev(this), next(this), key(data) { }
    private:
        /*
         * 屏蔽拷贝构造函数和赋值运算
         */
        DataListNode(DataListNode const &node) {}
        DataListNode & operator = (DataListNode const &node) {}
    public:
        bool is_sigular() const { return prev == this; }

        T & data() { return key; }
        T const & data() const { return key; }

        T & data_prev() { return prev->key; }
        T const & data_prev() const { return prev->key; }

        DataListNode & next_node() { return *next; }
        DataListNode * next_ptr() { return next; }
        DataListNode & prev_node() { return *prev; }
        DataListNode * prev_ptr() { return prev; }

        T & data_next() { return next->key; }
        T const & data_next() const { return next->key; }
    public:
        void init() {
            this->next = this;
            this->prev = this;
        }

        void add(DataListNode * n) {
            this->next->prev = n;
            n->next = this->next;
            n->prev = this;
            this->next = n;
        }
 
        DataListNode * add(T const & data) {
            DataListNode * n = new DataListNode(data);
            next->prev = n;
            n->next = next;
            n->prev = this;
            this->next = n;

            return next;
        }

        void add_prev(DataListNode * p) {
            this->prev->next = p;
            p->prev = this->prev;
            p->next = this;
            this->prev = p;
        }
 
        DataListNode * add_prev(T const & data) {
            DataListNode * p = new DataListNode(data);
            prev->next = p;
            p->prev = prev;
            p->next = this;
            this->prev = p;

            return prev;
        }

        void remove() {
            next->prev = prev;
            prev->next = next;
            next = this;
            prev = this;
        }

        /*
         * replace - 替换节点
         */
        friend void replace(DataListNode * o, DataListNode * n) {
            n->next = o->next;
            n->next->prev = n;
            n->prev = o->prev;
            n->prev->next = n;
        }

        friend void swap(DataListNode * u, DataListNode * v) {
            DataListNode tmp;

            replace(u, &tmp);
            replace(v, u);
            replace(&tmp, v);
        }


    public:
        DataListNode & operator = (T const &data) {
            key = data;
        }

    public:
        T key;
    private:
        DataListNode * prev;
        DataListNode * next;
};

#endif

