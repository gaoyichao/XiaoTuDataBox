#ifndef __ARRAY2D_HPP__
#define __ARRAY2D_HPP__

#include <iostream>
#include <cassert>

template <class T>
class Array2D {
    public:
        Array2D() : array(NULL), rows(0), cols(0) {}
        Array2D(int r, int c) : array(NULL), rows(0), cols(0) { resize(r, c); }
        Array2D(int r, int c, T const & v) : array(NULL), rows(0), cols(0)
        {
            resize(r, c);
            int n = r * c;
            for (int i = 0; i < n; i++)
                array[i] = v;
        }

        ~Array2D()
        {
            if (NULL != array)
                delete [] array;
        }

        void resize(int r, int c, T const & v)
        {
            resize(r, c);
            int n = r * c;
            for (int i = 0; i < n; i++)
                array[i] = v;
        }
        void resize(int r, int c)
        {
            if (0 == r || 0 == c) {
                delete [] array;
                array = NULL;
                rows = 0;
                cols = 0;
            }

            if (r == rows && c == cols)
                return;

            int n = r * c;
            T * arr = new T[n];
            int rr = (r < rows) ? r : rows;
            int cc = (c < cols) ? c : cols;

            for (int i = 0; i < rr; i++)
            for (int j = 0; j < cc; j++)
                arr[i * cols + j] = array[i * cols + j];

            delete [] array;

            array = arr;
            rows = r;
            cols = c;
        }

        T & at(int n)
        {
            assert(n < (rows * cols));
            return array[n];
        }


        T & at(int r, int c)
        {
            if (r > rows || c > cols) {
                int rr = (r > rows) ? r : rows;
                int cc = (c > cols) ? c : cols;
                resize(rr, cc);
            }

            return array[r * cols + c];
        }

        T const & at(int n) const
        {
            assert(n < (rows * cols));
            return array[n];
        }

        T const & at(int r, int c) const
        {
            assert(r < rows);
            assert(c < cols);

            return array[r * cols + c];
        }

        T & operator () (int n) { return at(n); }
        T & operator () (int r, int c) { return at(r, c); }
        T const & operator () (int n) const { return at(n); }
        T const & operator () (int r, int c) const { return at(r, c); }

        friend std::ostream & operator << (std::ostream & stream, Array2D const & array) {
            int r, c;
            array.size(r, c);

            if (r <= 0 || c <= 0)
                return stream;

            r = r - 1;
            for (int i = 0; i < r; i++) {
                stream << "| " << array(i, 0);
                for (int j = 1; j < c; j++)
                    stream << "\t" << array(i, j);
                stream << " |" << std::endl;
            }

            stream << "| " << array(r, 0);
            for (int j = 1; j < c; j++)
                stream << "\t" << array(r, j);
            stream << " |";

            return stream;
        }

        int size() const { return rows * cols; }
        int size(int & r, int & c) const
        {
            r = rows;
            c = cols;
            return r * c;
        }
    private:
        T *array;
        int rows;
        int cols;
};

#endif


