#ifndef DATA_QUEUE_HPP
#define DATA_QUEUE_HPP

#include <iostream>
#include <cassert>

template <class T>
class DataQueue {
    public:
        /*
         * 默认构造函数,初始容量为4
         */
        DataQueue() {
            mStorBegin = new T[4];
            mStorEnd = mStorBegin + 4;
            mBegin = mStorBegin;
            mEnd = 0;
        }
        /*
         * 析构函数
         */
        ~DataQueue() {
            if (0 != mStorBegin)
                delete [] mStorBegin;
        }

    public:
        int capacity() const { return mStorEnd - mStorBegin; }
        int size() const {
            if (0 == mEnd)
                return 0;
            if (mBegin < mEnd)
                return mEnd - mBegin;
            else
                return (mStorEnd - mBegin) + (mEnd - mStorBegin);
        }
        int available() const { return capacity() - size(); }
        bool empty() const { return 0 == mEnd; }
        bool full() const { return mEnd == mBegin; }

    public:
        /*
         * clear - 清空队列
         */
        void clear() {
            mBegin = mStorBegin;
            mEnd = 0;
        }
        /*
         * ajust_capacity - 调整队列容量
         *
         * @c: 容量
         */
        int adjust_capacity(int c) {
            int s = size();
            if (c < s) {
                rearrange();
                return 1;
            }

            if (c == capacity()) {
                rearrange();
                return 0;
            }

            T *tmp = new T[c];
            T *begin = mStorBegin;

            int i = 0;
            if (mBegin < mEnd) {
                for (i = 0; i < s; i++)
                    tmp[i] = mBegin[i];
            } else {
                while (mBegin != mStorEnd) {
                    tmp[i] = mBegin[0];
                    mBegin++;
                    i++;
                }
                while (begin != mEnd) {
                    tmp[i] = begin[0];
                    begin++;
                    i++;
                }
            }

            delete [] mStorBegin;
            mStorBegin = tmp;
            mStorEnd = mStorBegin + c;
            mBegin = mStorBegin;
            mEnd = mStorBegin + s;

            return 0;
        }
        /*
         * rearrange - 整理queue
         */
        void rearrange() {
            if (mStorBegin == mBegin)
                return;

            int c = capacity();
            int s = size();

            T *tmp = new T[c];
            T *begin = mStorBegin;
            int i = 0;

            if (mBegin < mEnd) {
                for (i = 0; i < s; i++)
                    tmp[i] = mBegin[i];
            } else {
                while (mBegin != mStorEnd) {
                    tmp[i] = mBegin[0];
                    mBegin++;
                    i++;
                }
                while (begin != mEnd) {
                    tmp[i] = begin[0];
                    begin++;
                    i++;
                }
            }

            delete [] mStorBegin;
            mStorBegin = tmp;
            mStorEnd = mStorBegin + c;
            mBegin = mStorBegin;
            mEnd = mStorBegin + s;
        }

        bool push_front(T const & e) {
            if (full())
                adjust_capacity(2 * capacity());

            if (empty())
                mEnd = mBegin;

            mBegin--;
            if (mBegin < mStorBegin)
                mBegin = mStorEnd - 1;
            mBegin[0] = e;

            return true;
        }

        bool push_back(T const & e) {
            if (full())
                adjust_capacity(2 * capacity());

            if (empty())
                mEnd = mBegin;

            mEnd[0] = e;
            mEnd++;
            if (mEnd == mStorEnd)
                mEnd = mStorBegin;

            return true;
        }

        bool pop_front(T & buf) {
            if (empty())
                return false;

            buf = mBegin[0];
            mBegin++;

            if (mBegin == mStorEnd)
                mBegin = mStorBegin;
            if (mBegin == mEnd) {
                mBegin = mStorBegin;
                mEnd = 0;
            }

            return true;
        }

        bool pop_back(T & buf) {
            if (empty())
                return false;

            mEnd--;
            if (mEnd < mStorBegin)
                mEnd = mStorEnd - 1;

            buf = mEnd[0];

            if (mBegin == mEnd) {
                mBegin = mStorBegin;
                mEnd = 0;
            }

            return true;
        }

        bool peek_front(T & buf) {
            if (empty())
                return false;

            buf = mBegin[0];

            return true;
        }

        bool peek_back(T & buf) {
            if (empty())
                return false;

            T *tmp = mEnd - 1;
            if (tmp < mStorBegin)
                tmp = mStorEnd - 1;

            buf = *tmp;
            return true;
        }

        bool enqueue(T const & e) { return push_back(e); }
        bool dequeue(T & buf) { return pop_front(buf); }

    private:
        T *mStorBegin;
        T *mStorEnd;
        T *mBegin;
        T *mEnd;
};




#endif

