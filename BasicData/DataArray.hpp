#ifndef DATA_ARRAY_HPP
#define DATA_ARRAY_HPP

#include <iostream>
#include <cassert>

template <class T>
class DataArray {
    public:
        /*
         * 默认构造函数
         */
        DataArray() : mStorBegin(0), mStorEnd(0), mEnd(0) { }
        /*
         * 构造函数
         *
         * @size: 构建数组大小
         */
        DataArray(int size) {
            int c = 4;
            while (c < size)
                c *= 2;

            mStorBegin = new T[c];
            mStorEnd = mStorBegin + c;
            mEnd = mStorBegin + size;
        }
        /*
         * 构造函数
         *
         * @buf: 初值元素缓存
         * @len: 数组大小
         */
        DataArray(T const *buf, int len) {
            int c = 1;
            while (c < len)
                c *= 2;

            mStorBegin = new T[c];
            mStorEnd = mStorBegin + c;
            mEnd = mStorBegin + len;

            for (int i = 0; i < len; i++)
                mStorBegin[i] = buf[i];
        }
        /*
         * 拷贝构造函数
         */
        DataArray(DataArray const & array) {
            int c = array.capacity();
            int n = array.size();
            
            mStorBegin = new T[c];
            mStorEnd = mStorBegin + c;
            mEnd = mStorBegin + n;

            for (int i = 0; i < n; i++)
                mStorBegin[i] = array[i];
        }
        /*
         * 析构函数
         */
        ~DataArray() {
            if (0 != mStorBegin)
                delete [] mStorBegin;
        }

    public:
        int capacity() const { return mStorEnd - mStorBegin; }
        int size() const { return mEnd - mStorBegin; }
        int available() const { return mStorEnd - mEnd; }
        bool empty() const { return mEnd == mStorBegin; }
        bool full() const { return mStorEnd == mEnd; }

    public:
        /*
         * ajust_capacity - 调整数组容量
         *
         * @c: 容量
         */
        int adjust_capacity(int c) {
            int n = size();
            if (c < n)
                return 1;

            if (c == capacity())
                return 0;

            int capacity = c > 0 ? c : 1;
            T *tmp = new T[capacity];
            for (int i = 0; i < n; i++)
                tmp[i] = mStorBegin[i];

            delete [] mStorBegin;
            mStorBegin = tmp;
            mStorEnd = mStorBegin + capacity;
            mEnd = mStorBegin + n;

            return 0;
        }
        /*
         * resize - 调整数组大小
         */
        int resize(int size) {
            int cap = this->capacity();
            while (cap < size)
                cap *= 2;

            int err = adjust_capacity(cap);
            if (0 != err)
                return err;

            mEnd = mStorBegin + size;
            return 0;
        }
        /*
         * clear - 清空数组
         */
        void clear() {
            mEnd = mStorBegin;
        }
        /*
         * find - 查找元素返回指针
         */
        T* find(T const & e) const {
            for (T *p = mStorBegin; p < mEnd; p++) {
                if (e == *p)
                    return p;
            }
        
            return 0;
        }
        /*
         * find_idx - 查找元素返回索引
         */
        int find_idx(T const & e) const {
            int n = size();
        
            for (int i = 0; i < n; i++)
                if (e == mStorBegin[i])
                    return i;
        
            return -1;
        }
        /*
         * has - 判定是否有某个元素
         */
        bool has(T const & e) const {
            return (0 != find(e));
        }
        /*
         * insert - 插入元素
         *
         * @i: 插入目标位置
         * @e: 目标元素
         */
        int insert(int i, T const & e) {
            int n = size();
            if (i > n)
                return 1;

            int err = resize(n + 1);
            if (0 != err)
                return err;

            if (i < n) {
                for (int idx = n; idx >= i; idx--)
                    mStorBegin[idx] = mStorBegin[idx-1];
            }
            mStorBegin[i] = e;
            return 0;
        }
        /*
         * insert -向数组中的第i个位置上插入len个元素
         *
         * @i: 目标索引[0,n]
         * @buf: 元素缓存 
         * @len: 元素数量
         */
        int insert(int i, T const *buf, int len) {
            int n = size();
            if (i > n)
                return 1;
        
            int err = resize(n + len);
            if (0 != err)
                return err;
        
            if (i < n) {
                for (int idx = n; idx >= i; idx--)
                    mStorBegin[idx + len - 1] = mStorBegin[idx-1];
            }

            for (int idx = 0; idx < len; idx++)
                mStorBegin[idx + i] = buf[idx];
            return 0;
        }
        /*
         * remove - 移除一段数据[from, to)
         *
         * @from: 移除段起始索引,从0开始
         * @to: 移除段结束索引,从0开始
         */
        int remove(int from, int to) {
            if (to < from)
                return 1;
        
            int n = size();
            if (to >= n)
                return 2;

            int len = n - to;
            for (int idx = 0; idx < len; idx++)
                mStorBegin[from + idx] = mStorBegin[to + idx];
 
            mEnd -= (to - from);
            return 0;
        }
        /*
         * remove - 移除一个数据
         *
         * @id: 移除的目标数据索引
         */
        int remove(int id) {
            return remove(id, id+1);
        }

    public:
        T const & operator [] (int idx) const {
            assert((mStorBegin + idx) < mStorEnd);
            return mStorBegin[idx];
        }

        T & operator [] (int idx) {
            assert((mStorBegin + idx) < mStorEnd);
            return mStorBegin[idx];
        }

        DataArray & operator = (DataArray const &array) {
            int n = array.size();

            if (this->capacity() < n) {
                delete mStorBegin;

                int c = array.capacity();
                mStorBegin = new T[c];
                mStorEnd = mStorBegin + c;
            }

            for (int i = 0; i < n; i++)
                mStorBegin[i] = array[i];
            mEnd = mStorBegin + n;

            return *this;
        }

        friend std::ostream & operator << (std::ostream & stream, DataArray const & array) {
            stream << "[";

            int n = array.size();
            if (n > 0)
                stream << array[0];

            for (int i = 1; i < n; i++)
                stream << ", " << array[i];

            stream << "]";

            return stream;
        }


    private:
        T *mStorBegin;
        T *mStorEnd;
        T *mEnd;
};

#endif

