#ifndef DATA_LIST_HPP
#define DATA_LIST_HPP

#include <DataListNode.hpp>

/*
 * DataList - 双向循环列表
 */
template <class T>
class DataList {
    public:
        /*
         * 默认构造函数
         */
        DataList() : mSize(0) {}
        /*
         * 构造函数
         *
         * @size: 构建链表大小
         */
        DataList(int size) : mSize(0) {
            if (size <= 0)
                return;

            for (int i = 0; i < size; i++) {
                mHead.add_prev(new DataListNode<T>());
                mSize++;
            }
        }
        /*
         * 构造函数
         *
         * @buf: 初值元素缓存
         * @len: 链表大小
         */
        DataList(T const *buf, int len) : mSize(0) {
            if (len <= 0)
                return;

            for (int i = 0; i < len; i++) {
                mHead.add_prev(new DataListNode<T>(buf[i]));
                mSize++;
            }
        }
 
        ~DataList() {
            clear();
        }
    public:
        bool empty() const { return mHead.prev == &mHead; }
        int size() const { return mSize; }

    public:
        DataListNode<T> * begin() {
            return mHead.next;
        }

        DataListNode<T> * end() {
            return &mHead;
        }

        DataListNode<T> & first() {
            return *(mHead.next);
        }

    public:
        void clear() {
            DataListNode<T> *end = &mHead;
            DataListNode<T> *cur = mHead.next;
            DataListNode<T> *next = cur->next;

            while (cur != end) {
                delete cur;
                cur = next;
                next = cur->next;
            }
            mHead.init();
        }

        DataListNode<T> * insert(DataListNode<T> * node, T const & v) {
            DataListNode<T> *re = new DataListNode<T>(v);
            node->add(re);
            mSize++;
            return re;
        }

        DataListNode<T> * insert_prev(DataListNode<T> * node, T const & v) {
            DataListNode<T> *re = new DataListNode<T>(v);
            node->add_prev(re);
            mSize++;
            return re;
        }


        void remove(DataListNode<T> *node) {
            node->remove();
            delete node;
            mSize--;
        }

        DataListNode<T> * find(T const & e) {
            DataListNode<T> *end = &mHead;
            for (DataListNode<T> *ptr = mHead.next; ptr != end; ptr = ptr->next) {
                if (e == ptr->data())
                    return ptr;
            }
            return 0;
        }

        DataListNode<T> * push(T const & v) {
            return insert(&mHead, v);
        }

        T pop() {
            T re = mHead.next->key;
            remove(mHead.next);
            return re;
        }

        void pop(T & re) {
            re = mHead.next->key;
            remove(mHead.next);
        }

        DataListNode<T> * push_end(T const & v) {
            return insert_prev(&mHead, v);
        }

        T pop_end() {
            T re = mHead.prev->key;
            remove(mHead.prev);
            return re;
        }

        void pop_end(T & re) {
            re = mHead.prev->key;
            remove(mHead.prev);
        }

        DataListNode<T> * enqueue(T const & v) {
            return insert_prev(&mHead, v);
        }

        T dequeue() {
            T re = mHead.next->key;
            remove(mHead.next);
            return re;
        }

        void dequeue(T & re) {
            re = mHead.next->key;
            remove(mHead.next);
        }


        DataListNode<T> * enqueue_head(T const & v) {
            return insert(&mHead, v);
        }

        T dequeue_end() {
            T re = mHead.prev->key;
            remove(mHead.prev);
            return re;
        }

        void dequeue_end(T & re) {
            re = mHead.prev->key;
            remove(mHead.prev);
        }

    protected:
        DataListNode<T> mHead;
        int mSize;
};

#endif

